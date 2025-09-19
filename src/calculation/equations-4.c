/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:13:14 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 21:14:03 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vec3	get_cone_apex(t_cone *cone, t_vec3 axis)
{
	return (add_vec3(cone->center, scale_vec3(axis, cone->height * 3.0 / 4.0)));
}

static void	compute_quadratic_coeffs(t_ray *ray, t_vec3 *vecs, double abcd[4],
		double *mesur)
{
	double	k;

	k = pow(mesur[0] / 2 / mesur[1], 2);
	abcd[3] = k;
	abcd[0] = dot_vec3(ray->direction, ray->direction) - (1 + k)
		* pow(dot_vec3(ray->direction, vecs[1]), 2);
	abcd[1] = 2 * (dot_vec3(ray->direction, vecs[0]) - (1 + k)
			* dot_vec3(ray->direction, vecs[1]) * dot_vec3(vecs[0], vecs[1]));
	abcd[2] = dot_vec3(vecs[0], vecs[0]) - (1 + k) * pow(dot_vec3(vecs[0],
				vecs[1]), 2);
}

static double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 > 0.00001 && (t2 < 0.00001 || t1 < t2))
		return (t1);
	if (t2 > 0.00001)
		return (t2);
	return (-1.0);
}

static bool	validate_cone_hit(t_cone *cone, t_vec3 hit_point, t_vec3 apex,
		t_vec3 axis)
{
	double	projection;
	double	radius_at_hit;
	t_vec3	base_point;

	projection = dot_vec3(sub_vec3(hit_point, apex), axis);
	if (projection < 0 || projection > cone->height + EPSILON)
		return (false);
	radius_at_hit = (cone->diameter / 2) * (projection / cone->height);
	base_point = add_vec3(apex, scale_vec3(axis, projection));
	if (length_vec3(sub_vec3(hit_point, base_point)) > radius_at_hit + EPSILON)
		return (false);
	return (true);
}

t_hit_info	intersect_cone_side(t_ray *ray, t_cone *cone)
{
	t_hit_info	hit;
	t_vec3		axis;
	t_vec3		apex;
	t_vec3		oc;
	t_vec3		hit_point;

	double (t), abcd[4];
	hit.distance = -1.0;
	hit.hit = false;
	axis = normalize_vec3(cone->axis);
	apex = get_cone_apex(cone, axis);
	oc = sub_vec3(ray->origin, apex);
	compute_quadratic_coeffs(ray, (t_vec3 [2]){oc, axis}, abcd,
		(double [2]){cone->diameter, cone->height});
	t = solve_quadratic(abcd[0], abcd[1], abcd[2]);
	if (t < 0.00001)
		return (hit);
	hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
	if (!validate_cone_hit(cone, hit_point, apex, axis))
		return (hit);
	hit.distance = t;
	hit.point = hit_point;
	hit.color = cone->color;
	hit.normal = get_cone_normal(cone, hit.point);
	return ((hit.hit = true), hit);
}
