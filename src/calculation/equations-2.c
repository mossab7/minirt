/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:19:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 18:03:23 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	screen_to_world(int x, int y)
{
	t_vec3				result;
	static const double	width_inv = 2.0 / WIN_WIDTH;
	static const double	height_inv = 2.0 / WIN_HEIGHT;

	result.x = (x * width_inv) - 1.0;
	result.y = (y * height_inv) - 1.0;
	result.z = 0.0;
	return (result);
}

t_ray	shoot_ray(t_scene *scene, t_vec3 screen_pos)
{
	t_ray	ray;
	t_vec3	direction;
	t_vec3	vertical;
	t_vec3	horizontal;

	vertical = scale_vec3(scene->camera.up, screen_pos.y
			* scene->camera.height);
	horizontal = scale_vec3(scene->camera.right, screen_pos.x
			* scene->camera.width);
	direction = scene->camera.direction;
	direction = add_vec3(direction, horizontal);
	direction = add_vec3(direction, vertical);
	ray.origin = scene->camera.position;
	ray.direction = normalize_vec3(direction);
	return (ray);
}

t_hit_info	intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_hit_info	hit_info;

	double (a), b, c, discriminant, t1, t2;
	hit_info.distance = -1.0;
	hit_info.hit = false;
	a = dot_vec3(ray->direction, ray->direction);
	b = 2.0 * dot_vec3(sub_vec3(ray->origin, sphere->center), ray->direction);
	c = dot_vec3(sub_vec3(ray->origin, sphere->center), sub_vec3(ray->origin,
				sphere->center)) - (sphere->diameter * sphere->diameter) / 4.0;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_info);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0.001)
		hit_info.distance = t1;
	else if (t2 > 0.001)
		hit_info.distance = t2;
	else
		return (hit_info);
	hit_info.point = add_vec3(ray->origin,
			scale_vec3(ray->direction, hit_info.distance));
	hit_info.normal = normalize_vec3(sub_vec3(hit_info.point,
				sphere->center));
	return ((hit_info.color = sphere->color), (hit_info.hit = true), hit_info);
}

t_hit_info	compute_cylinder_hit(t_ray *ray, t_cylinder *cylinder,
		t_vec3 axis, double *val)
{
	t_hit_info	hit;
	t_vec3		hit_point;
	t_vec3		center_to_hit;
	t_vec3		axis_point;

	double (t1), t2, t, projection;
	hit.hit = false;
	hit.distance = -1.0;
	t1 = (-val[2] - sqrt(val[0])) / (2 * val[1]);
	t2 = (-val[2] + sqrt(val[0])) / (2 * val[1]);
	t = *(double *)ternary((t1 > 0.001), &t1, &t2);
	if (t < 0.001)
		return (hit);
	hit_point = add_vec3(ray->origin, scale_vec3(ray->direction, t));
	center_to_hit = sub_vec3(hit_point, cylinder->center);
	projection = dot_vec3(center_to_hit, axis);
	if (fabs(projection) > cylinder->height / 2)
		return (hit);
	axis_point = add_vec3(cylinder->center, scale_vec3(axis, projection));
	hit.point = hit_point;
	hit.normal = normalize_vec3(sub_vec3(hit_point, axis_point));
	hit.distance = t;
	return ((hit.hit = true), (hit.color = cylinder->color), hit);
}
