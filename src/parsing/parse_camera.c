/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:27:25 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:47:34 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	dgree_to_rad(double degree)
{
	return ((degree * M_PI) / 180.0);
}

void	parse_camera(t_scene *scene, t_str *line)
{
	size_t	count;
	t_str	*fields;

	str_peek_reset(line);
	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	scene->camera.position = extract_vec3(&fields[1]);
	scene->camera.direction = extract_normalvec(&fields[2]);
	scene->camera.fov = extract_fov(&fields[3]);
	end_of_line_parse(fields, count, 3);
	if (get_error_system()->code)
	{
		str_free_array(fields, count);
		return ;
	}
	scene->camera.direction = add_vec3(scene->camera.direction,
			(t_vec3){EPSILON, EPSILON, EPSILON});
	scene->camera.direction = normalize_vec3(scene->camera.direction);
	scene->camera.width = tan(dgree_to_rad(scene->camera.fov / 2));
	scene->camera.height = scene->camera.width / (16.0f / 9.0f);
	str_free_array(fields, count);
	recalculate_camera_vectors(&scene->camera);
}
