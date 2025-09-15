/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:35 by deepseeko         #+#    #+#             */
/*   Updated: 2025/09/15 01:49:01 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "texture.h"
#include <math.h>
#include <stdbool.h>


static double	grad(int hash, double x, double y)
{
	int	h;

	h = hash & 3;
	if (h == 0)
		return (x + y);
	else if (h == 1)
		return (-x + y);
	else if (h == 2)
		return (x - y);
	else
		return (-x - y);
}

double	noise_function(double x, double y)
{
	int(xi), yi;
	double(xf), yf, u, v, g00, g01, g10, g11;
	init_permutation_table();
	xi = (int)floor(x) & 255;
	yi = (int)floor(y) & 255;
	xf = x - floor(x);
	yf = y - floor(y);
	u = fade(xf);
	v = fade(yf);
	g00 = grad(get_perm()[get_perm()[xi] + yi], xf, yf);
	g01 = grad(get_perm()[get_perm()[xi] + yi + 1], xf, yf - 1);
	g10 = grad(get_perm()[get_perm()[xi + 1] + yi], xf - 1, yf);
	g11 = grad(get_perm()[get_perm()[xi + 1] + yi + 1], xf - 1, yf - 1);
	return (lerp(v, lerp(u, g00, g10), lerp(u, g01, g11)));
}


t_vec3	apply_bump_mapping(t_hit_info *hit_info, t_pattern *pattern)
{
	if (pattern && (pattern->type & PATTERN_BUMP_MAP))
		return (calculate_bump_normal(hit_info, pattern));
	return (hit_info->normal);
}

t_color	get_pattern_color(t_hit_info *hit_info, void *object)
{
	t_pattern	*pattern;
	t_color		base_color;
	t_color		texture_color;
	double		alpha;

	pattern = NULL;
	if (hit_info->object_type == SPHERE)
	{
		pattern = &((t_sphere *)object)->pattern;
		base_color = ((t_sphere *)object)->color;
	}
	else if (hit_info->object_type == PLANE)
	{
		pattern = &((t_plane *)object)->pattern;
		base_color = ((t_plane *)object)->color;
	}
	else if (hit_info->object_type == CYLINDER)
	{
		pattern = &((t_cylinder *)object)->pattern;
		base_color = ((t_cylinder *)object)->color;
	}
	else if (hit_info->object_type == CONE)
	{
		pattern = &((t_cone *)object)->pattern;
		base_color = ((t_cone *)object)->color;
	}
	else
		return ((t_color){0, 0, 0});
	if (pattern && (pattern->type & PATTERN_TEXTURE))
	{
		texture_color = apply_texture(hit_info, pattern);
		alpha = 0.5;
		return ((t_color){texture_color.r * (1.0 - alpha) + base_color.r
			* alpha, texture_color.g * (1.0 - alpha) + base_color.g * alpha,
			texture_color.b * (1.0 - alpha) + base_color.b * alpha});
	}
	if (pattern && (pattern->type & PATTERN_CHECKERBOARD))
		return (apply_checkerboard_pattern(hit_info, pattern));
	return (base_color);
}

t_color	apply_texture(t_hit_info *hit_info, t_pattern *pattern)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	up;

	double(u), v;
	int(tex_x), tex_y;
	if (hit_info->object_type == SPHERE)
	{
		u = 0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI);
		v = 0.5 - asin(hit_info->normal.y) / M_PI;
	}
	else if (hit_info->object_type == PLANE)
	{
		up = (t_vec3){0.0, 1.0, 0.0};
		if (fabs(dot_vec3(hit_info->normal, up)) > 0.999)
			up = (t_vec3){1.0, 0.0, 0.0};
		u_axis = normalize_vec3(cross_vec3(hit_info->normal, up));
		v_axis = cross_vec3(hit_info->normal, u_axis);
		u = dot_vec3(hit_info->point, u_axis);
		v = dot_vec3(hit_info->point, v_axis);
	}
	else if (hit_info->object_type == CYLINDER)
	{
		u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		v = hit_info->point.y;
	}
	else if (hit_info->object_type == CONE)
	{
		u = atan2(hit_info->point.x, hit_info->point.z) / (2 * M_PI);
		v = hit_info->point.y;
	}
	else
	{
		u = 0;
		v = 0;
	}
	u = u - floor(u);
	v = v - floor(v);
	tex_x = (int)(u * pattern->texture->width);
	tex_y = (int)(v * pattern->texture->height);
	return (get_pixel_color(pattern->texture, tex_x, tex_y));
}
