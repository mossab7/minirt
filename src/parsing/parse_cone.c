/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj-1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:20:11 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:25:07 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	fill_cone(t_object *obj, t_str *fields)
{
	obj->type = CONE;
	obj->u_obj.cone.center = sub_vec3(extract_vec3(&fields[1]),
			scale_vec3(obj->u_obj.cone.axis, obj->u_obj.cone.height));
	obj->u_obj.cone.axis = extract_vec3(&fields[2]);
	obj->u_obj.cone.diameter = ft_atof(fields[3].data);
	obj->u_obj.cone.height = ft_atof(fields[4].data);
	obj->u_obj.cone.color = extract_color(&fields[5]);
}

void	parse_cone(t_scene *scene, t_str *line)
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
	fill_cone(obj, fields);
	obj->pattern.type = PATTERN_NONE;
	if (count > 6)
		extract_pattern(fields, &obj->pattern, count, 6);
	if (get_error_system()->code)
	{
		container_push_back(scene->objects, obj);
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->objects, obj);
}
