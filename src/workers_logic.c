/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:37:12 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 21:41:45 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	worker1job(t_worker *worker, t_pixel_batch *batch, int *batch_count)
{
	int (i) = 0;
	if (*batch_count >= BATCH_SIZE)
	{
		pthread_mutex_lock(&worker->program->render_mutex);
		while (i < *batch_count)
		{
			put_pixel_to_image(worker->program->mlx->canvas, batch[i].x,
				batch[i].y, batch[i].color);
			i++;
		}
		pthread_mutex_unlock(&worker->program->render_mutex);
		*batch_count = 0;
	}
}

static void	worker2job(t_worker *worker, t_pixel_batch *batch, int *batch_count)
{
	int (i) = 0;
	if (*batch_count > 0)
	{
		pthread_mutex_lock(&worker->program->render_mutex);
		while (i < *batch_count)
		{
			put_pixel_to_image(worker->program->mlx->canvas, batch[i].x,
				batch[i].y, batch[i].color);
			i++;
		}
		pthread_mutex_unlock(&worker->program->render_mutex);
	}
}

void	worker_render_scene(t_worker *worker)
{
	t_pixel_batch	batch[BATCH_SIZE];
	t_vec3			screen_pos;
	t_ray			ray;
	t_color			color;

	int (x), (y), (batch_count);
	batch_count = 0;
	y = worker->start_y - 1;
	while (++y < worker->end_y)
	{
		x = worker->start_x;
		while (x < worker->end_x)
		{
			screen_pos = screen_to_world(x, y);
			ray = shoot_ray(worker->program->scene, screen_pos);
			color = trace_ray(worker->program->scene, &ray);
			batch[batch_count].x = x;
			batch[batch_count].y = y;
			batch[batch_count].color = color;
			batch_count++;
			worker1job(worker, batch, &batch_count);
			x++;
		}
	}
	worker2job(worker, batch, &batch_count);
}

long	get_num_cores_unix(void)
{
	long	num_cores;

	num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	if (num_cores > 0)
		return (num_cores);
	return (1);
}
