/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:54:38 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/19 21:55:18 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

#define DEFAULT_SPECULAR 0.5
#define DEFAULT_DIFFUSE 0.9
#define DEFAULT_SHININESS 32.0

static double	compute_diffuse_intensity(t_scene *scene, t_hit_info *hit_info,
		t_vec3 normal, t_light *light)
{
	double	diffuse;
	t_vec3	light_dir;

	light_dir = compute_light_dir(hit_info, light);
	diffuse = fmax(0.0, dot_vec3(normal, light_dir)) * light->intensity;
	if (is_in_shadow(scene, hit_info, light))
		diffuse = 0.0;
	return (diffuse);
}

static double	compute_specular_intensity(t_hit_info *hit_info, t_vec3 normal,
		t_vec3 light_dir, t_scene *scene)
{
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	spec_factor;
	double	specular;

	view_dir = normalize_vec3(sub_vec3(scene->camera.position,
				hit_info->point));
	reflect_dir = sub_vec3(scale_vec3(normal, 2 * dot_vec3(light_dir, normal)),
			light_dir);
	spec_factor = pow(fmax(0.0, dot_vec3(view_dir, reflect_dir)),
			DEFAULT_SHININESS);
	specular = DEFAULT_SPECULAR * spec_factor;
	return (specular);
}

static void	accumulate_light(t_color *final_color, t_color base_color,
		t_light *light, double val[2])
{
	final_color->r += base_color.r * val[0] * DEFAULT_DIFFUSE + val[1]
		* light->color.r;
	final_color->g += base_color.g * val[0] * DEFAULT_DIFFUSE + val[1]
		* light->color.g;
	final_color->b += base_color.b * val[0] * DEFAULT_DIFFUSE + val[1]
		* light->color.b;
}

static t_vec3	get_surface_normal(t_hit_info *hit_info)
{
	t_pattern	*pattern;

	pattern = get_object_pattern(hit_info);
	if (pattern && (pattern->type & PATTERN_BUMP_MAP))
		return (apply_bump_mapping(hit_info, pattern));
	return (hit_info->normal);
}

t_color	calculate_lighting(t_scene *scene, t_hit_info *hit_info)
{
	t_color	base_color;
	t_color	final_color;
	t_vec3	surface_normal;
	t_vec3	light_dir;
	t_light	*light;

	double (i), diffuse, specular;
	base_color = get_pattern_color(hit_info);
	surface_normal = get_surface_normal(hit_info);
	final_color = scale_color(base_color, scene->amb_light.ratio);
	i = 0;
	while (i < scene->lights->size)
	{
		light = get_light(scene->lights, i);
		light_dir = compute_light_dir(hit_info, light);
		diffuse = compute_diffuse_intensity(scene, hit_info, surface_normal,
				light);
		specular = compute_specular_intensity(hit_info, surface_normal,
				light_dir, scene) * diffuse;
		accumulate_light(&final_color, base_color, light, (double [2]){diffuse,
			specular});
		i++;
	}
	return (final_color);
}
