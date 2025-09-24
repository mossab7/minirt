/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:08:25 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/16 18:08:41 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	parse_sphare(char **data, t_scene *scene)
{
	t_sphere	sphere;
	t_object	*obj;

	sphere.center = get_vec3(data[1]);
	sphere.diameter = ft_atof(data[2]);
	if (sphere.diameter <= 0)
	{
		ft_putstr_fd("Error: Invalid sphere diameter\n", 2);
		safe_exit(1);
	}
	sphere.color = get_color(data[3]);
	obj = alloc(sizeof(t_object));
	if (data[4])
		parse_pattern(&data[4], &obj->pattern);
	else
		obj->pattern.type = PATTERN_NONE;
	obj->type = SPHERE;
	obj->u_obj.sphere = sphere;
	container_push_back(scene->objects, obj);
}

void	parse_plane(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = alloc(sizeof(t_object));
	obj->type = PLANE;
	obj->u_obj.plane.center = get_vec3(data[1]);
	obj->u_obj.plane.normal = get_vec3(data[2]);
	check_vec_range(obj->u_obj.plane.normal);
	obj->u_obj.plane.color = get_color(data[3]);
	if (data[4])
		parse_pattern(&data[4], &obj->pattern);
	else
		obj->pattern.type = PATTERN_NONE;
	container_push_back(scene->objects, obj);
}

void	parse_cylinder(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = alloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->u_obj.cylinder.center = get_vec3(data[1]);
	obj->u_obj.cylinder.axis = get_vec3(data[2]);
	check_vec_range(obj->u_obj.cylinder.axis);
	obj->u_obj.cylinder.diameter = ft_atof(data[3]);
	obj->u_obj.cylinder.height = ft_atof(data[4]);
	obj->u_obj.cylinder.color = get_color(data[5]);
	if (data[6])
		parse_pattern(&data[6], &obj->pattern);
	else
		obj->pattern.type = PATTERN_NONE;
	container_push_back(scene->objects, obj);
}

void	parse_cone(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = alloc(sizeof(t_object));
	obj->type = CONE;
	obj->u_obj.cone.center = sub_vec3(get_vec3(data[1]),
			scale_vec3(obj->u_obj.cone.axis, obj->u_obj.cone.height));
	obj->u_obj.cone.axis = get_vec3(data[2]);
	check_vec_range(obj->u_obj.cone.axis);
	obj->u_obj.cone.diameter = ft_atof(data[3]);
	obj->u_obj.cone.height = ft_atof(data[4]);
	obj->u_obj.cone.color = get_color(data[5]);
	if (obj->u_obj.cone.diameter <= 0 || obj->u_obj.cone.height <= 0)
	{
		ft_putstr_fd("Error: Invalid cone diameter or height\n", 2);
		safe_exit(1);
	}
	if (data[6])
		parse_pattern(&data[6], &obj->pattern);
	else
		obj->pattern.type = PATTERN_NONE;
	container_push_back(scene->objects, obj);
}

void	parse_hyperboloid(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = alloc(sizeof(t_object));
	obj->type = HYPERBOLDOID;
	obj->u_obj.hyperboloid.center = get_vec3(data[1]);
	obj->u_obj.hyperboloid.axis = get_vec3(data[2]);
	check_vec_range(obj->u_obj.hyperboloid.axis);
	obj->u_obj.hyperboloid.diameter = ft_atof(data[3]);
	obj->u_obj.hyperboloid.height = ft_atof(data[4]);
	obj->u_obj.hyperboloid.color = get_color(data[5]);
	container_push_back(scene->objects, obj);
}
