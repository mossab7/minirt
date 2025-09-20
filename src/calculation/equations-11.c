/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-11.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 01:26:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 01:31:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	render_pixel_batch(t_program *program,
		t_canvas *canvas, t_pixel_batch *batch, int batch_count)
{
	int	i;

	pthread_mutex_lock(&program->render_mutex);
	i = 0;
	while (i < batch_count)
	{
		put_pixel_to_image(canvas, batch[i].x, batch[i].y, batch[i].color);
		i++;
	}
	pthread_mutex_unlock(&program->render_mutex);
}

static void	process_pixel(t_scene *scene, int *xy,
	t_pixel_batch *batch, int *batch_count)
{
	t_vec3	screen_pos;
	t_ray	ray;
	t_color	color;

	screen_pos = screen_to_world(xy[0], xy[1]);
	ray = shoot_ray(scene, screen_pos);
	color = trace_ray(scene, &ray);
	batch[*batch_count].x = xy[0];
	batch[*batch_count].y = xy[1];
	batch[*batch_count].color = color;
	(*batch_count)++;
}

void	worker_render_scene(t_worker *worker)
{
	t_scene			*scene;
	t_canvas		*canvas;
	t_pixel_batch	batch[BATCH_SIZE];

	int (batch_count), x, y;
	t_program (*program) = worker->program;
	scene = program->scene;
	canvas = program->mlx->canvas;
	batch_count = 0;
	y = worker->start_y - 1;
	while (++y < worker->end_y)
	{
		x = worker->start_x - 1;
		while (++x < worker->end_x)
		{
			process_pixel(scene, (int [2]){x, y}, batch, &batch_count);
			if (batch_count >= BATCH_SIZE)
			{
				render_pixel_batch(program, canvas, batch, batch_count);
				batch_count = 0;
			}
		}
	}
	if (batch_count > 0)
		render_pixel_batch(program, canvas, batch, batch_count);
}

void	*worker_loop(void *arg)
{
	t_worker (*worker) = (t_worker *)arg;
	t_program (*program) = worker->program;
	int (count) = 0;
	while (++count)
	{
		pthread_mutex_lock(&program->main_mutex);
		while ((!program->render_flag && program->program_running) || count > 1)
		{
			pthread_cond_wait(&program->render_cond, &program->main_mutex);
			count = 1;
		}
		if (!program->program_running)
		{
			pthread_mutex_unlock(&program->main_mutex);
			break ;
		}
		pthread_mutex_unlock(&program->main_mutex);
		worker_render_scene(worker);
		pthread_mutex_lock(&program->main_mutex);
		program->worker_finish_count++;
		if (program->worker_finish_count >= program->num_workers)
			pthread_cond_signal(&program->completion_cond);
		pthread_mutex_unlock(&program->main_mutex);
	}
	return (NULL);
}
