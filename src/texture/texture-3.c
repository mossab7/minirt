/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture-3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 01:50:03 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/15 03:14:20 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	fil_uv(double *u, double *v, )
{
	t_cone	*cone;
	t_vec3	axis;
	t_vec3	vec_from_base;

	if (hit_info->object_type == SPHERE)
	{
		u = (0.5 + atan2(hit_info->normal.z, hit_info->normal.x) / (2 * M_PI)) * pattern->scale;
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
	else if (hit_info->object_type == CONE)
	{
		cone = &hit_info->object->obj.cone;
		axis = normalize_vec3(cone->axis);
		vec_from_base = sub_vec3(hit_info->point, cone->center);
		u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		v = dot_vec3(vec_from_base, axis);
		u *= pattern->scale;
		v *= pattern->scale;
	}
	return (0);
}
t_vec3	calculate_bump_normal(t_hit_info *hit_info, t_pattern *pattern)
{

	t_vec3 tangent, bitangent, perturbed_normal;
	double (u), v, bump_u, bump_v, delta;
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
	else if (hit_info->object_type == CONE)
	{
		cone = &hit_info->object->obj.cone;
		axis = normalize_vec3(cone->axis);
		vec_from_base = sub_vec3(hit_info->point, cone->center);
		u = atan2(hit_info->normal.x, hit_info->normal.z) / (2 * M_PI);
		v = dot_vec3(vec_from_base, axis);
		u *= pattern->scale;
		v *= pattern->scale;
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
	perturbed_normal = add_vec3(perturbed_normal, scale_vec3(tangent, bump_u
				* pattern->bump_strength));
	perturbed_normal = add_vec3(perturbed_normal, scale_vec3(bitangent, bump_v
				* pattern->bump_strength));
	return (normalize_vec3(perturbed_normal));
}
