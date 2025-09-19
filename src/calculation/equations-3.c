/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:40:57 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 17:07:00 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_hit_info	intersect_cylinder_side(t_ray *ray, t_cylinder *cylinder)
{
	t_hit_info	hit;
	t_vec3		axis;
	t_vec3		oc;

	double (a), b, c, discriminant, rd_dot_axis, oc_dot_axis;
	hit.hit = false;
	hit.distance = -1.0;
	axis = normalize_vec3(cylinder->axis);
	oc = sub_vec3(ray->origin, cylinder->center);
	rd_dot_axis = dot_vec3(ray->direction, axis);
	oc_dot_axis = dot_vec3(oc, axis);
	a = dot_vec3(ray->direction, ray->direction) - rd_dot_axis * rd_dot_axis;
	b = 2 * (dot_vec3(ray->direction, oc) - rd_dot_axis * oc_dot_axis);
	c = dot_vec3(oc, oc) - oc_dot_axis * oc_dot_axis
		- pow(cylinder->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit);
	return (compute_cylinder_hit(ray, cylinder, axis,
			(double [3]){discriminant, a, b}));
}

static t_vec3	get_cap_center(t_cylinder *cylinder, t_vec3 axis, int cap_side)
{
	return (add_vec3(cylinder->center,
			scale_vec3(axis, cap_side * (cylinder->height / 2))));
}

static bool	intersect_cap_plane(t_ray *ray, t_vec3 cap_center,
				t_vec3 cap_normal, double *t)
{
	double	denom;

	denom = dot_vec3(cap_normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	*t = dot_vec3(sub_vec3(cap_center, ray->origin), cap_normal) / denom;
	if (*t < 0.001)
		return (false);
	return (true);
}

static bool	is_inside_cap(t_vec3 hit_point, t_vec3 cap_center,
				t_vec3 axis, double radius)
{
	t_vec3	to_center;
	t_vec3	radial_component;

	to_center = sub_vec3(hit_point, cap_center);
	radial_component = sub_vec3(to_center,
			scale_vec3(axis, dot_vec3(to_center, axis)));
	return (length_vec3(radial_component) <= radius);
}

t_hit_info	intersect_cylinder_cap(t_ray *ray,
			t_cylinder *cylinder, int cap_side)
{
	t_hit_info	hit;
	t_vec3		axis;
	t_vec3		cap_center;
	t_vec3		cap_normal;
	t_vec3		hit_point;

	double (t), radius;
	hit.distance = -1.0;
	hit.hit = false;
	axis = normalize_vec3(cylinder->axis);
	cap_center = get_cap_center(cylinder, axis, cap_side);
	cap_normal = scale_vec3(axis, cap_side);
	if (!intersect_cap_plane(ray, cap_center, cap_normal, &t))
		return (hit);
	hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
	radius = cylinder->diameter / 2;
	if (!is_inside_cap(hit_point, cap_center, axis, radius))
		return (hit);
	hit.distance = t;
	hit.point = hit_point;
	hit.normal = cap_normal;
	hit.color = cylinder->color;
	hit.hit = true;
	return (hit);
}
