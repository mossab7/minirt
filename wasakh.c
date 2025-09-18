/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasakh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:00:34 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/17 18:50:13 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdbool.h>
#include "../includes/transform_object.h"
#include "../includes/camera.h"

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
