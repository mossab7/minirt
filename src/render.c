/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:38:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 16:35:39 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minirt.h>

#define DEFAULT_SPECULAR 0.5
#define DEFAULT_DIFFUSE 0.9
#define DEFAULT_SHININESS 32.0

bool		is_in_shadow(t_scene *scene, t_hit_info *hit_info, t_light *light);

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
	apex = add_vec3(cone->center, scale_vec3(axis, cone->height)); // Apex is at base_center + axis * height
	v = sub_vec3(point, apex); // Vector from apex to hit point
	height = cone->height;
	radius = cone->diameter / 2;
	k = pow(radius / height, 2); // (radius/height)^2
	m = dot_vec3(v, axis); // Projection of v onto axis
	normal = sub_vec3(v, scale_vec3(axis, m * (1 + k))); // Normal points outwards from the cone surface
	normal = normalize_vec3(normal);

	return (normal);
}

static t_pattern	*get_object_pattern(t_hit_info *hit_info)
{
	if (!hit_info->object)
		return (NULL);
	return (&hit_info->object->pattern);
}

t_color	calculate_lighting(t_scene *scene, t_hit_info *hit_info)
{
	t_color		base_color;
	t_color		final_color;
	t_vec3		light_dir;
	t_vec3		surface_normal;
	double		light_intensity;
	t_pattern	*pattern;
	t_material	material;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		specular_factor;
	double		specular_intensity;
	t_light		*light;
	size_t		i;

	material.specular = DEFAULT_SPECULAR;
	material.diffuse = DEFAULT_DIFFUSE;
	material.shininess = DEFAULT_SHININESS;

	base_color = get_pattern_color(hit_info);
	pattern = get_object_pattern(hit_info);
	if (pattern && (pattern->type & PATTERN_BUMP_MAP))
		surface_normal = apply_bump_mapping(hit_info, pattern);
	else
		surface_normal = hit_info->normal;

	final_color = scale_color(base_color, scene->amb_light.ratio);
	i = 0;
	while (i < scene->lights->size)
	{
		light = get_light(scene->lights, i);
		light_dir = normalize_vec3(sub_vec3(light->position,
				hit_info->point));
		light_intensity = fmax(0.0, dot_vec3(surface_normal, light_dir)) * light->intensity;
		if (is_in_shadow(scene, hit_info, light))
			light_intensity = 0.0;

		view_dir = normalize_vec3(sub_vec3(scene->camera.position, hit_info->point));
		reflect_dir = sub_vec3(scale_vec3(surface_normal, 2 * dot_vec3(light_dir, surface_normal)), light_dir);
		specular_factor = pow(fmax(0.0, dot_vec3(view_dir, reflect_dir)), material.shininess);
		specular_intensity = material.specular * specular_factor * light_intensity;

		final_color.r += base_color.r * light_intensity * material.diffuse + specular_intensity * light->color.r;
		final_color.g += base_color.g * light_intensity * material.diffuse + specular_intensity * light->color.g;
		final_color.b += base_color.b * light_intensity * material.diffuse + specular_intensity * light->color.b;
		i++;
	}
	return (final_color);
}

t_hit_info	find_closest_intersection(t_container *objects, t_ray *ray)
{
	t_object	*object;
	double		closest_distance;
	size_t		i;
	t_hit_info	hit_info;
	t_hit_info	closest_hit;

	closest_distance = -1.0;
	closest_hit.distance = -1.0;
	closest_hit.hit = false;
	for (i = 0; i < objects->size; i++)
	{
		object = get_object(objects, i);
		if (object->type == SPHERE)
			hit_info = intersect_sphere(ray, &object->obj.sphere);
		else if (object->type == PLANE)
			hit_info = intersect_plane(ray, &object->obj.plane);
		else if (object->type == CYLINDER)
			hit_info = intersect_cylinder(ray, &object->obj.cylinder);
		else if (object->type == CONE)
			hit_info = intersect_cone(ray, &object->obj.cone);
		else
			continue ;
		if (hit_info.hit && hit_info.distance > 0
			&& (closest_distance < 0
				|| hit_info.distance < closest_distance))
		{
			closest_distance = hit_info.distance;
			closest_hit = hit_info;
			closest_hit.object_type = object->type;
			closest_hit.object = object;
		}
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

t_color	trace_ray(t_scene *scene, t_ray *ray)
{
	t_hit_info	hit_info;
	t_color		color;

	hit_info = find_closest_intersection(scene->objects, ray);
	if (!hit_info.hit || hit_info.distance < 0)
	{
		return (scale_color(scene->amb_light.color, scene->amb_light.ratio));
	}
	color = calculate_lighting(scene, &hit_info);
	return (color);
}

void	put_pixel_to_image(t_canvas *canvas, int x, int y,
		t_color color)
{
	char	*dst;
	int		int_color;
	int		r;
	int		g;
	int		b;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	r = (int)(fmin(1.0, fmax(0.0, color.r)) * 255);
	g = (int)(fmin(1.0, fmax(0.0, color.g)) * 255);
	b = (int)(fmin(1.0, fmax(0.0, color.b)) * 255);
	int_color = (r << 16) | (g << 8) | b;
	dst = canvas->addr + (y * canvas->line_length
			+ x * (canvas->bpp / 8));
	*(unsigned int *)dst = int_color;
}

int	render_scene(t_program *program)
{
	pthread_mutex_lock(&program->main_mutex);
	program->render_flag = true;
	program->worker_finish_count = 0;
	pthread_cond_broadcast(&program->render_cond);
	pthread_mutex_unlock(&program->main_mutex);

	pthread_mutex_lock(&program->main_mutex);
	while (program->worker_finish_count < program->num_workers)
	{
		pthread_cond_wait(&program->completion_cond, &program->main_mutex);
	}
	program->render_flag = false;
	mlx_put_image_to_window(program->mlx->mlx_ptr,
	program->mlx->win_ptr, program->mlx->canvas->img_ptr, 0, 0);
	pthread_mutex_unlock(&program->main_mutex);
	return (0);
}
