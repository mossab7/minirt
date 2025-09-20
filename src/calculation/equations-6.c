/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:50:51 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 21:51:23 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_hit_info	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_hit_info	hit_info;
	t_hit_info	side_hit;
	t_hit_info	top_cap_hit;
	t_hit_info	bottom_cap_hit;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	side_hit = intersect_cylinder_side(ray, cylinder);
	top_cap_hit = intersect_cylinder_cap(ray, cylinder, 1);
	bottom_cap_hit = intersect_cylinder_cap(ray, cylinder, -1);
	if (side_hit.hit && (!top_cap_hit.hit
			|| side_hit.distance < top_cap_hit.distance)
		&& (!bottom_cap_hit.hit
			|| side_hit.distance < bottom_cap_hit.distance))
		hit_info = side_hit;
	else if (top_cap_hit.hit && (!bottom_cap_hit.hit
			|| top_cap_hit.distance < bottom_cap_hit.distance))
		hit_info = top_cap_hit;
	else if (bottom_cap_hit.hit)
		hit_info = bottom_cap_hit;
	return (hit_info);
}

t_hit_info	intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit_info	hit_info;
	double		denom;
	double		t;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	denom = dot_vec3(plane->normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (hit_info);
	t = dot_vec3(sub_vec3(plane->center, ray->origin), plane->normal) / denom;
	if (t < 0.001)
		return (hit_info);
	hit_info.distance = t;
	hit_info.point = add_vec3(ray->origin,
			scale_vec3(ray->direction, hit_info.distance));
	hit_info.normal = plane->normal;
	hit_info.color = plane->color;
	hit_info.hit = true;
	return (hit_info);
}

t_vec3	get_cone_normal(t_cone *cone, t_vec3 point)
{
	t_vec3	normal;
	t_vec3	axis;
	t_vec3	apex;
	t_vec3	v;

	double (m), k, radius, height;
	axis = normalize_vec3(cone->axis);
	apex = add_vec3(cone->center, scale_vec3(axis, cone->height));
	v = sub_vec3(point, apex);
	height = cone->height;
	radius = cone->diameter / 2;
	k = pow(radius / height, 2);
	m = dot_vec3(v, axis);
	normal = sub_vec3(v, scale_vec3(axis, m * (1 + k)));
	normal = normalize_vec3(normal);
	return (normal);
}

t_pattern	*get_object_pattern(t_hit_info *hit_info)
{
	if (!hit_info->object)
		return (NULL);
	return (&hit_info->object->pattern);
}
