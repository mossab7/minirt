/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:01:57 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 22:02:03 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	compute_light_dir(t_hit_info *hit_info, t_light *light)
{
	return (normalize_vec3(sub_vec3(light->position, hit_info->point)));
}

static t_hit_info	intersect_object(t_object *object, t_ray *ray)
{
	t_hit_info	no_hit;

	if (object->type == SPHERE)
		return (intersect_sphere(ray, &object->obj.sphere));
	else if (object->type == PLANE)
		return (intersect_plane(ray, &object->obj.plane));
	else if (object->type == CYLINDER)
		return (intersect_cylinder(ray, &object->obj.cylinder));
	else if (object->type == CONE)
		return (intersect_cone(ray, &object->obj.cone));
	no_hit.hit = false;
	no_hit.distance = -1.0;
	return (no_hit);
}

static void	update_closest_hit(t_hit_info *closest_hit,
		double *closest_distance, t_hit_info hit_info, t_object *object)
{
	if (hit_info.hit && hit_info.distance > 0
		&& (*closest_distance < 0 || hit_info.distance < *closest_distance))
	{
		*closest_distance = hit_info.distance;
		*closest_hit = hit_info;
		closest_hit->object_type = object->type;
		closest_hit->object = object;
	}
}

t_hit_info	find_closest_intersection(t_container *objects, t_ray *ray)
{
	t_hit_info	closest_hit;
	t_hit_info	hit_info;
	t_object	*object;
	double		closest_distance;
	size_t		i;

	closest_distance = -1.0;
	closest_hit.hit = false;
	closest_hit.distance = -1.0;
	i = 0;
	while (i < objects->size)
	{
		object = get_object(objects, i);
		hit_info = intersect_object(object, ray);
		update_closest_hit(&closest_hit, &closest_distance, hit_info, object);
		i++;
	}
	return (closest_hit);
}

bool	is_in_shadow(t_scene *scene, t_hit_info *hit_info, t_light *light)
{
	t_ray		shadow_ray;
	t_hit_info	shadow_hit;
	double		light_distance;

	shadow_ray.origin = hit_info->point;
	shadow_ray.direction = normalize_vec3(sub_vec3(light->position,
				hit_info->point));
	shadow_ray.origin = add_vec3(shadow_ray.origin,
			scale_vec3(shadow_ray.direction, 0.001));
	light_distance = length_vec3(sub_vec3(light->position,
				hit_info->point));
	shadow_hit = find_closest_intersection(scene->objects, &shadow_ray);
	return (shadow_hit.hit && shadow_hit.distance > 0
		&& shadow_hit.distance < light_distance);
}
