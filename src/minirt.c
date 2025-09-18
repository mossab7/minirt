/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:59 by deepseeko         #+#    #+#             */
/*   Updated: 2025/09/17 17:23:19 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include "../includes/transform_object.h"
#include "../includes/camera.h"
#include "texture.h"
#include <X11/keysym.h>
#include <mlx.h>
#include <stdio.h>

void	safe_exit(int status)
{
	t_program	*program;
	int i;

	program = *get_program();
	if (program->workers)
	{
		pthread_mutex_lock(&program->main_mutex);
		program->program_running = false;
		program->render_flag = true;
		pthread_cond_broadcast(&program->render_cond);
		pthread_mutex_unlock(&program->main_mutex);

		i = 0;
		while (i < program->num_workers)
		{
			pthread_join(program->workers[i].thread, NULL);
			i++;
		}
		pthread_mutex_destroy(&program->main_mutex);
		pthread_mutex_destroy(&program->render_mutex);
		pthread_cond_destroy(&program->render_cond);
		pthread_cond_destroy(&program->completion_cond);
	}
	free_all_textures(program->scene);
	if (program->mlx && program->mlx->canvas->img_ptr)
		mlx_destroy_image(program->mlx->mlx_ptr, program->mlx->canvas->img_ptr);
	if (program->mlx && program->mlx->win_ptr)
		mlx_destroy_window(program->mlx->mlx_ptr, program->mlx->win_ptr);
	if (program->mlx && program->mlx->mlx_ptr)
		mlx_destroy_display(program->mlx->mlx_ptr);
	cleanup_memory_tracker(get_memory_tracker());
	exit(status);
}

t_canvas	*init_canvas(void *mlx_ptr, int width, int height)
{
	t_canvas	*canvas;

	canvas = alloc(sizeof(t_canvas));
	canvas->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!canvas->img_ptr)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		safe_exit(1);
	}
	canvas->addr = mlx_get_data_addr(canvas->img_ptr, &canvas->bpp,
			&canvas->line_length, &canvas->endian);
	return (canvas);
}

t_mlx	*_init_mlx(void)
{
	t_mlx	*mlx;

	mlx = alloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		ft_putstr_fd("Error: Failed to initiate mlx connection\n", 2);
		safe_exit(1);
	}
	register_allocation(mlx->mlx_ptr, free);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"MiniRT");
	if (!mlx->win_ptr)
	{
		ft_putstr_fd("Error: Failed to create window\n", 2);
		safe_exit(1);
	}
	mlx->canvas = init_canvas(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	return (mlx);
}

int loop_hook(void *param)
{
	t_program *program;

	program = (t_program *)param;
	if (program->dirty)
	{
		render_scene(program);
		program->dirty = false;
	}
	return (0);
}



long get_num_cores_unix()
{
	long num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	if (num_cores > 0)
		return num_cores;
	return (1);
}

static void set_single_worker_bounds(t_worker *worker)
{
	worker->start_x = 0;
	worker->end_x = WIN_WIDTH;
	worker->start_y = 0;
	worker->end_y = WIN_HEIGHT;
}

// static void set_row_division_bounds(t_worker *workers, int num_threads)
// {
// 	int rows_per_thread = WIN_HEIGHT / num_threads;
// 	int i;

// 	for (i = 0; i < num_threads; i++)
// 	{
// 		workers[i].start_x = 0;
// 		workers[i].end_x = WIN_WIDTH;
// 		workers[i].start_y = i * rows_per_thread;

// 		if (i == num_threads - 1)
// 			workers[i].end_y = WIN_HEIGHT;
// 		else
// 			workers[i].end_y = (i + 1) * rows_per_thread;
// 	}
// }

static void set_grid_division_bounds(t_worker *workers, int num_threads)
{
	int sqrt_threads = (int)sqrt(num_threads);
	int tiles_x = sqrt_threads;
	int tiles_y = (num_threads + tiles_x - 1) / tiles_x;

	int cols_per_tile = WIN_WIDTH / tiles_x;
	int rows_per_tile = WIN_HEIGHT / tiles_y;
	int i, tile_x, tile_y;

	for (i = 0; i < num_threads; i++)
	{
		tile_x = i % tiles_x;
		tile_y = i / tiles_x;

		workers[i].start_x = tile_x * cols_per_tile;
		workers[i].start_y = tile_y * rows_per_tile;

		if (tile_x == tiles_x - 1)
			workers[i].end_x = WIN_WIDTH;
		else
			workers[i].end_x = (tile_x + 1) * cols_per_tile;

		if (tile_y == tiles_y - 1)
			workers[i].end_y = WIN_HEIGHT;
		else
			workers[i].end_y = (tile_y + 1) * rows_per_tile;
	}
}

void calculate_worker_bounds(t_program *program)
{
	int num_threads = program->num_workers;
	t_worker *workers = program->workers;

	if (num_threads == 1)
	{
		set_single_worker_bounds(&workers[0]);
	}
	else
	{
		set_grid_division_bounds(workers, num_threads);
		//set_row_division_bounds(workers, num_threads);
	}
	// else
	// {
	// }
}

void worker_render_scene(t_worker *worker)
{
	t_program *program = worker->program;
	t_scene *scene = program->scene;
	t_canvas *canvas = program->mlx->canvas;
	int x, y;

	t_pixel_batch batch[BATCH_SIZE];
	int batch_count = 0;

	y = worker->start_y;
	while (y < worker->end_y)
	{
		x = worker->start_x;
		while (x < worker->end_x)
		{
			t_vec3 screen_pos = screen_to_world(x, y);
			t_ray ray = shoot_ray(scene, screen_pos);
			t_color color = trace_ray(scene, &ray);

			batch[batch_count].x = x;
			batch[batch_count].y = y;
			batch[batch_count].color = color;
			batch_count++;

			if (batch_count >= BATCH_SIZE)
			{
				pthread_mutex_lock(&program->render_mutex);
				for (int i = 0; i < batch_count; i++)
				{
					put_pixel_to_image(canvas, batch[i].x, batch[i].y, batch[i].color);
				}
				pthread_mutex_unlock(&program->render_mutex);
				batch_count = 0;
			}
			x++;
		}
		y++;
	}
	if (batch_count > 0)
	{
		pthread_mutex_lock(&program->render_mutex);
		for (int i = 0; i < batch_count; i++)
		{
			put_pixel_to_image(canvas, batch[i].x, batch[i].y, batch[i].color);
		}
		pthread_mutex_unlock(&program->render_mutex);
	}
}


void *worker_loop(void *arg)
{
    t_worker *worker = (t_worker *)arg;
    t_program *program = worker->program;
	int count = 1;

    while (1)
    {
        pthread_mutex_lock(&program->main_mutex);
        while ((!program->render_flag && program->program_running) || count > 1 )
		{
            pthread_cond_wait(&program->render_cond, &program->main_mutex);
			count = 1;
		}
        if (!program->program_running)
        {
            pthread_mutex_unlock(&program->main_mutex);
            break;
        }
        pthread_mutex_unlock(&program->main_mutex);

        worker_render_scene(worker);

        pthread_mutex_lock(&program->main_mutex);
        program->worker_finish_count++;
        if (program->worker_finish_count >= program->num_workers)
        {
            pthread_cond_signal(&program->completion_cond);
        }
        pthread_mutex_unlock(&program->main_mutex);
		count++;
    }

    return NULL;
}


void set_up_workers(t_program *program)
{
    int			num_threads;
    t_worker	*workers;
    int			i;

    num_threads = get_num_cores_unix();
    // if (num_threads > 8)
    //     num_threads = 8;
    workers = alloc(sizeof(t_worker) * num_threads);
    program->num_workers = num_threads;
    program->workers = workers;
    program->program_running = true;
    program->render_flag = false;
    program->worker_finish_count = 0;

    if (pthread_mutex_init(&program->main_mutex, NULL) != 0 ||
        pthread_mutex_init(&program->render_mutex, NULL) != 0 ||
        pthread_cond_init(&program->render_cond, NULL) != 0 ||
        pthread_cond_init(&program->completion_cond, NULL) != 0)
    {
        ft_putstr_fd("Error: Failed to initialize threading primitives\n", 2);
        safe_exit(1);
    }

    calculate_worker_bounds(program);

    for (i = 0; i < num_threads; i++)
    {
        workers[i].program = program;
        if (pthread_create(&workers[i].thread, NULL, worker_loop, &workers[i]) != 0)
        {
            ft_putstr_fd("Error: Failed to create thread\n", 2);
            for (int j = 0; j < i; j++)
            {
                pthread_cancel(workers[j].thread);
                pthread_join(workers[j].thread, NULL);
            }
            safe_exit(1);
        }
    }

}

int	main(int argc, char **argv)
{
	t_program	*program;


	if (argc != 2)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	program = *get_program();
	program->mlx = _init_mlx();
	program->scene = parse_scene(argv[1]);
	set_up_workers(program);
	render_scene(program);
	program->dirty = true;
	mlx_key_hook(program->mlx->win_ptr, key_hook, program);
	mlx_loop_hook(program->mlx->mlx_ptr, loop_hook, program);
	mlx_mouse_hook(program->mlx->win_ptr, mouse_hook, program);
	mlx_loop(program->mlx->mlx_ptr);
	safe_exit(0);
}

