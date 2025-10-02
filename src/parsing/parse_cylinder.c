/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:24:54 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 18:02:11 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	fill_cylinder(t_object *obj, t_str *fields)
{
	obj->type = CYLINDER;
	obj->u_obj.cylinder.center = extract_vec3(&fields[1]);
	obj->u_obj.cylinder.axis = extract_vec3(&fields[2]);
	obj->u_obj.cylinder.diameter = ft_atof(fields[3].data);
	obj->u_obj.cylinder.height = ft_atof(fields[4].data);
	obj->u_obj.cylinder.color = extract_color(&fields[5]);
}

void	parse_cylinder(t_scene *scene, t_str *line)
{
	t_object	*obj;
	t_str		*fields;
	size_t		count;

	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	if (count < 6)
	{
		set_error(7, "Missing fields");
		str_free_array(fields, count);
		return ;
	}
	obj = alloc(sizeof(t_object));
	fill_cylinder(obj, fields);
	obj->pattern.type = PATTERN_NONE;
	if (count > 6)
		extract_pattern(fields, &obj->pattern, count, 6);
	if (get_error_system()->code != 0)
	{
		container_push_back(scene->objects, obj);
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->objects, obj);
}
