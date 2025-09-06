/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:35 by deepseeko         #+#    #+#             */
/*   Updated: 2025/07/12 19:02:36 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_color	apply_checkerboard_pattern(t_hit_info *hit_info, t_pattern *pattern)
{
	double	u, v;
	int		checker_u, checker_v;

	if (hit_info->object_type == SPHERE)
	{
		u = 0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI);
		v = 0.5 - asin(hit_info->normal.y) / M_PI;
	}
	else if (hit_info->object_type == PLANE)
	{
		u = hit_info->point.x;
		v = hit_info->point.z;
	}
	else if (hit_info->object_type == CYLINDER)
	{
		u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		v = hit_info->point.y;
	}
	else
	{
		u = 0;
		v = 0;
	}
	checker_u = (int)floor(u * pattern->scale);
	checker_v = (int)floor(v * pattern->scale);
	if ((checker_u + checker_v) % 2 == 0)
		return (pattern->color1);
	return (pattern->color2);
}

double	noise_function(double x, double y)
{
	double	value;

	value = sin(x * 10.0) * cos(y * 10.0);
	value += 0.5 * sin(x * 20.0) * cos(y * 20.0);
	value += 0.25 * sin(x * 40.0) * cos(y * 40.0);
	return (value * 0.5);
}

t_vec3	calculate_bump_normal(t_hit_info *hit_info, t_pattern *pattern)
{
	double	u, v, bump_u, bump_v, delta;
	t_vec3	tangent, bitangent, perturbed_normal;

	if (hit_info->object_type == SPHERE)
	{
		u = 0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI);
		v = 0.5 - asin(hit_info->normal.y) / M_PI;
		u *= pattern->scale;
		v *= pattern->scale;
	}
	else if (hit_info->object_type == PLANE)
	{
		u = hit_info->point.x * pattern->scale;
		v = hit_info->point.z * pattern->scale;
	}
	else if (hit_info->object_type == CYLINDER)
	{
		u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		v = hit_info->point.y * pattern->scale;
	}
	else
		return (hit_info->normal);
	delta = 0.001;
	bump_u = noise_function(u + delta, v) - noise_function(u - delta, v);
	bump_v = noise_function(u, v + delta) - noise_function(u, v - delta);
	if (hit_info->object_type == SPHERE)
	{
		tangent = (t_vec3){-hit_info->normal.z, 0, hit_info->normal.x};
		if (length_vec3(tangent) < 0.001)
			tangent = (t_vec3){1, 0, 0};
		tangent = normalize_vec3(tangent);
		bitangent = normalize_vec3(cross_vec3(hit_info->normal, tangent));
	}
	else
	{
		tangent = (t_vec3){1, 0, 0};
		bitangent = (t_vec3){0, 0, 1};
	}
	perturbed_normal = hit_info->normal;
	perturbed_normal = add_vec3(perturbed_normal,
		scale_vec3(tangent, bump_u * pattern->bump_strength));
	perturbed_normal = add_vec3(perturbed_normal,
		scale_vec3(bitangent, bump_v * pattern->bump_strength));
	return (normalize_vec3(perturbed_normal));
}

t_vec3	apply_bump_mapping(t_hit_info *hit_info, t_pattern *pattern)
{
	if (pattern->type == PATTERN_BUMP_MAP)
		return (calculate_bump_normal(hit_info, pattern));
	return (hit_info->normal);
}

t_color	get_pattern_color(t_hit_info *hit_info, void *object)
{
	t_pattern	*pattern;

	pattern = NULL;
	if (hit_info->object_type == SPHERE)
	{
		pattern = &((t_sphere *)object)->pattern;
		if (pattern && pattern->type == PATTERN_CHECKERBOARD)
			return (apply_checkerboard_pattern(hit_info, pattern));
		return (((t_sphere *)object)->color);
	}
	else if (hit_info->object_type == PLANE)
	{
		pattern = &((t_plane *)object)->pattern;
		if (pattern && pattern->type == PATTERN_CHECKERBOARD)
			return (apply_checkerboard_pattern(hit_info, pattern));
		return (((t_plane *)object)->color);
	}
	else if (hit_info->object_type == CYLINDER)
	{
		pattern = &((t_cylinder *)object)->pattern;
		if (pattern && pattern->type == PATTERN_CHECKERBOARD)
			return (apply_checkerboard_pattern(hit_info, pattern));
		return (((t_cylinder *)object)->color);
	}
	return ((t_color){0, 0, 0});
}
