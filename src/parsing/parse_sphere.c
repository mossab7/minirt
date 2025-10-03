/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:49 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:25:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	fill_sphere(t_object *obj, t_str *fields)
{
	obj->type = SPHERE;
	obj->u_obj.sphere.center = extract_vec3(&fields[1]);
	obj->u_obj.sphere.diameter = extract_diameter(&fields[2]);
	obj->u_obj.sphere.color = extract_color(&fields[3]);
}

void	parse_sphere(t_scene *scene, t_str *line)
{
	size_t		count;
	t_str		*fields;
	t_object	*obj;

	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	if (count < 4)
	{
		set_error(7, "Missing fields");
		str_free_array(fields, count);
		return ;
	}
	obj = alloc(sizeof(t_object));
	fill_sphere(obj, fields);
	obj->pattern.type = PATTERN_NONE;
	if (count > 4)
		extract_pattern(fields, &obj->pattern, count, 4);
	if (get_error_system()->code != 0)
	{
		container_push_back(scene->objects, obj);
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->objects, obj);
}
