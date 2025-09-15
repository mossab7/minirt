/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:07:36 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 22:08:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	register_allocation(void *ptr, void (*free_func)(void *))
{
	register_memory_allocation(get_memory_tracker(), create_memory_record(ptr,
			free_func));
}

static void	thread_destroy(t_program *program)
{
	int (i) = 0;
	pthread_mutex_lock(&program->main_mutex);
	program->program_running = false;
	program->render_flag = true;
	pthread_cond_broadcast(&program->render_cond);
	pthread_mutex_unlock(&program->main_mutex);
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

void	safe_exit(int status)
{
	t_program	*program;

	program = *get_program();
	if (program->workers)
		thread_destroy(program);
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
