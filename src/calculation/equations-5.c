/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:32:03 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 21:35:16 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

#define BASE_OFFSET 2 // Example offset, adjust as needed

static t_vec3	get_cone_base_center(t_cone *cone, t_vec3 axis)
{
	return (add_vec3(sub_vec3(cone->center,
				scale_vec3(axis, cone->height / 4.0)),
			scale_vec3(axis, cone->height * BASE_OFFSET)));
}

static bool	intersect_plane_cone(t_ray *ray, t_vec3 plane_point,
				t_vec3 plane_normal, double *t)
{
	double	denom;

	denom = dot_vec3(plane_normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	*t = dot_vec3(sub_vec3(plane_point, ray->origin), plane_normal) / denom;
	if (*t < 0.00001)
		return (false);
	return (true);
}

static bool	is_inside_base(t_vec3 hit_point, t_vec3 center, double radius)
{
	return (length_vec3(sub_vec3(hit_point, center)) <= radius + EPSILON);
}

t_hit_info	intersect_cone_base(t_ray *ray, t_cone *cone)
{
	t_hit_info	hit;
	t_vec3		axis;
	t_vec3		base_center;
	t_vec3		base_normal;
	t_vec3		hit_point;

	double (t), radius;
	hit.distance = -1.0;
	hit.hit = false;
	axis = normalize_vec3(cone->axis);
	base_center = get_cone_base_center(cone, axis);
	base_normal = scale_vec3(axis, -1.0);
	if (!intersect_plane_cone(ray, base_center, base_normal, &t))
		return (hit);
	hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
	radius = cone->diameter / 2;
	if (!is_inside_base(hit_point, base_center, radius))
		return (hit);
	hit.distance = t;
	hit.point = hit_point;
	hit.normal = base_normal;
	hit.color = cone->color;
	hit.hit = true;
	return (hit);
}

t_hit_info	intersect_cone(t_ray *ray, t_cone *cone)
{
	t_hit_info	hit_info;
	t_hit_info	side_hit;
	t_hit_info	base_hit;

	hit_info.distance = -1.0;
	hit_info.hit = false;
	side_hit = intersect_cone_side(ray, cone);
	base_hit = intersect_cone_base(ray, cone);
	if (side_hit.hit
		&& (!base_hit.hit || side_hit.distance < base_hit.distance))
		hit_info = side_hit;
	else if (base_hit.hit)
		hit_info = base_hit;
	return (hit_info);
}
