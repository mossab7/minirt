/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing-5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:55:03 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/17 03:09:13 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include "texture.h"

t_texture	*load_texture(char *filename)
{
	t_program	*program;
	t_texture	*texture;

	program = *get_program();
	texture = ft_calloc(1, sizeof(t_texture));
	handle_allocation_failure(texture);
	texture->img_ptr = mlx_xpm_file_to_image(program->mlx->mlx_ptr, filename,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		free(texture);
		ft_putstr_fd("Error: Failed to load texture file: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		safe_exit(1);
	}
	register_memory_allocation(get_memory_tracker(),
		create_memory_record(texture, free_texture));
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp,
			&texture->line_length, &texture->endian);
	return (texture);
}


t_color	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*dst;
	int		color_val;
	t_color	color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return ((t_color){1, 0, 1});
	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color_val = *(unsigned int *)dst;
	color.r = ((color_val >> 16) & 0xFF) / 255.0;
	color.g = ((color_val >> 8) & 0xFF) / 255.0;
	color.b = (color_val & 0xFF) / 255.0;
	return (color);
}
static void	calc_plane(t_hit_info *hit_info, double *u, double *v)
{
	t_vec3	up;

	up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(dot_vec3(hit_info->normal, up)) > 0.999)
		up = (t_vec3){1.0, 0.0, 0.0};
	*u = dot_vec3(hit_info->point,
			normalize_vec3(cross_vec3(hit_info->normal, up)));
	*v = dot_vec3(hit_info->point, cross_vec3(hit_info->normal,
				normalize_vec3(cross_vec3(hit_info->normal, up))));
}

static void	fil_uv(t_hit_info *hit_info, double *u, double *v)
{
	if (hit_info->object_type == SPHERE)
	{
		*u = 0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI);
		*v = 0.5 - asin(hit_info->normal.y) / M_PI;
	}
	else if (hit_info->object_type == PLANE)
		calc_plane(hit_info, u, v);
	else if (hit_info->object_type == CYLINDER)
	{
		*u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		*v = hit_info->point.y;
	}
	else if (hit_info->object_type == CONE)
	{
		*u = atan2(hit_info->point.x, hit_info->point.z) / (2 * M_PI);
		*v = hit_info->point.y;
	}
	else
	{
		*u = 0;
		*v = 0;
	}
}

t_color	apply_texture(t_hit_info *hit_info, t_pattern *pattern)
{
	double (u), v;
	int (tex_x), tex_y;
	fil_uv(hit_info, &u, &v);
	u = u - floor(u);
	v = v - floor(v);
	tex_x = (int)(u * pattern->texture->width);
	tex_y = (int)(v * pattern->texture->height);
	return (get_pixel_color(pattern->texture, tex_x, tex_y));
}
