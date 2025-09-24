/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:07:52 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 15:51:37 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	parse_amb_light(char **data, t_scene *scene)
{
	scene->amb_light.ratio = ft_atof(data[1]);
	if (scene->amb_light.ratio < LIGHT_RATIO_MIN
		|| scene->amb_light.ratio > LIGHT_RATIO_MAX)
	{
		ft_putstr_fd("Error: Invalid ambient light ratio\n", 2);
		safe_exit(1);
	}
	scene->amb_light.color = get_color(data[2]);
}

void	check_vec_range(t_vec3 vec)
{
	if (vec.x < VEC_MIN || vec.x > VEC_MAX || vec.y < VEC_MIN || vec.y > VEC_MAX
		|| vec.z < VEC_MIN || vec.z > VEC_MAX)
	{
		fprintf(stderr, "Error: Invalid vector range %f,%f,%f\n", vec.x, vec.y,
			vec.z);
		safe_exit(1);
	}
}

double	dgree_to_rad(double degree)
{
	return ((degree * M_PI) / 180.0);
}

void	parse_camera(char **data, t_scene *scene)
{
	scene->camera.position = get_vec3(data[1]);
	scene->camera.direction = get_vec3(data[2]);
	check_vec_range(scene->camera.direction);
	scene->camera.fov = ft_atof(data[3]);
	if (scene->camera.fov < FOV_MIN || scene->camera.fov > FOV_MAX)
	{
		ft_putstr_fd("Error: Invalid camera FOV\n", 2);
		safe_exit(1);
	}
	scene->camera.direction = add_vec3(scene->camera.direction,
			(t_vec3){EPSILON, EPSILON, EPSILON});
	scene->camera.direction = normalize_vec3(scene->camera.direction);
	scene->camera.width = tan(dgree_to_rad(scene->camera.fov / 2));
	scene->camera.height = scene->camera.width / (16.0f / 9.0f);
	recalculate_camera_vectors(&scene->camera);
}

void	parse_light(char **data, t_scene *scene)
{
	t_light	*light;

	light = (t_light *)alloc(sizeof(t_light));
	light->position = get_vec3(data[1]);
	light->intensity = ft_atof(data[2]);
	if (light->intensity > 1.0f || light->intensity < 0.0f)
	{
		ft_putstr_fd("Error: Invalid light intensity\n", 2);
		safe_exit(1);
	}
	light->color = get_color(data[3]);
	container_push_back(scene->lights, light);
}
