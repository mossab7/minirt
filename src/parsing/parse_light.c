/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:26:34 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:26:40 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	parse_light(t_scene *scene, t_str *line)
{
	size_t	count;
	t_str	*fields;
	t_light	*light;

	light = (t_light *)alloc(sizeof(t_light));
	str_peek_reset(line);
	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	if (count < 4)
	{
		set_error(7, "Missing fields");
		str_free_array(fields, count);
		return ;
	}
	light->position = extract_vec3(&fields[1]);
	light->intensity = extract_ratio(&fields[2]);
	light->color = extract_color(&fields[3]);
	end_of_line_parse(fields, count, 3);
	if (get_error_system()->code)
	{
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->lights, light);
}
