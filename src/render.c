/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:38:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 16:35:39 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minirt.h>

t_color	trace_ray(t_scene *scene, t_ray *ray)
{
	t_hit_info	hit_info;
	t_color		color;

	hit_info = find_closest_intersection(scene->objects, ray);
	if (!hit_info.hit || hit_info.distance < 0)
	{
		return (scale_color(scene->amb_light.color, scene->amb_light.ratio));
	}
	color = calculate_lighting(scene, &hit_info);
	return (color);
}

void	put_pixel_to_image(t_canvas *canvas, int x, int y,
		t_color color)
{
	char	*dst;
	int		int_color;
	int		r;
	int		g;
	int		b;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	r = (int)(fmin(1.0, fmax(0.0, color.r)) * 255);
	g = (int)(fmin(1.0, fmax(0.0, color.g)) * 255);
	b = (int)(fmin(1.0, fmax(0.0, color.b)) * 255);
	int_color = (r << 16) | (g << 8) | b;
	dst = canvas->addr + (y * canvas->line_length
			+ x * (canvas->bpp / 8));
	*(unsigned int *)dst = int_color;
}

int	render_scene(t_program *program)
{
	pthread_mutex_lock(&program->main_mutex);
	program->render_flag = true;
	program->worker_finish_count = 0;
	pthread_cond_broadcast(&program->render_cond);
	pthread_mutex_unlock(&program->main_mutex);
	pthread_mutex_lock(&program->main_mutex);
	while (program->worker_finish_count < program->num_workers)
		pthread_cond_wait(&program->completion_cond, &program->main_mutex);
	program->render_flag = false;
	mlx_put_image_to_window(program->mlx->mlx_ptr,
		program->mlx->win_ptr, program->mlx->canvas->img_ptr, 0, 0);
	pthread_mutex_unlock(&program->main_mutex);
	return (0);
}
