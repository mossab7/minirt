/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing-4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:48:16 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/17 15:30:12 by deepseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	apply_bump_mapping(t_hit_info *hit_info, t_pattern *pattern)
{
	if (pattern && (pattern->type & PATTERN_BUMP_MAP))
		return (calculate_bump_normal(hit_info, pattern));
	return (hit_info->normal);
}

static t_color	get_base_color(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->obj.sphere.color);
	if (obj->type == PLANE)
		return (obj->obj.plane.color);
	if (obj->type == CYLINDER)
		return (obj->obj.cylinder.color);
	if (obj->type == CONE)
		return (obj->obj.cone.color);
	if (obj->type == HYPERBOLDOID)
		return (obj->obj.hyperboloid.color);
	if (obj->type == PARABOLOID)
		return (obj->obj.paraboloid.color);
	return ((t_color){0, 0, 0});
}

t_color	get_pattern_color(t_hit_info *hit_info)
{
	t_pattern	*pattern;
	t_color		base_color;
	t_color		texture_color;

	pattern = &hit_info->object->pattern;
	base_color = get_base_color(hit_info->object);
	if (pattern && (pattern->type & PATTERN_TEXTURE))
	{
		texture_color = apply_texture(hit_info, pattern);
		return ((t_color){texture_color.r * (1.0 - ALPHA) + base_color.r
			* ALPHA, texture_color.g * (1.0 - ALPHA) + base_color.g * ALPHA,
			texture_color.b * (1.0 - ALPHA) + base_color.b * ALPHA});
	}
	if (pattern && (pattern->type & PATTERN_CHECKERBOARD))
		return (apply_checkerboard_pattern(hit_info, pattern));
	return (base_color);
}