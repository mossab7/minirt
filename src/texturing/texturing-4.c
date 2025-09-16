/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing-4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:48:16 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/16 21:56:40 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	apply_bump_mapping(t_hit_info *hit_info, t_pattern *pattern)
{
	if (pattern && (pattern->type & PATTERN_BUMP_MAP))
		return (calculate_bump_normal(hit_info, pattern));
	return (hit_info->normal);
}

static void	fil_patt(t_hit_info *hit_info, t_pattern **pattern,
		void *object, t_color *base_color)
{
	if (hit_info->object_type == SPHERE)
	{
		*pattern = &((t_sphere *)object)->pattern;
		*base_color = ((t_sphere *)object)->color;
	}
	else if (hit_info->object_type == PLANE)
	{
		*pattern = &((t_plane *)object)->pattern;
		*base_color = ((t_plane *)object)->color;
	}
	else if (hit_info->object_type == CYLINDER)
	{
		*pattern = &((t_cylinder *)object)->pattern;
		*base_color = ((t_cylinder *)object)->color;
	}
	else if (hit_info->object_type == CONE)
	{
		*pattern = &((t_cone *)object)->pattern;
		*base_color = ((t_cone *)object)->color;
	}
}

t_color	get_pattern_color(t_hit_info *hit_info, void *object)
{
	t_pattern	*pattern;
	t_color		base_color;
	t_color		texture_color;

	pattern = NULL;
	if (hit_info->object_type == SPHERE || hit_info->object_type == PLANE
		|| hit_info->object_type == CYLINDER || hit_info->object_type == CONE)
		fil_patt(hit_info, &pattern, object, &base_color);
	else
		return ((t_color){0, 0, 0});
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
