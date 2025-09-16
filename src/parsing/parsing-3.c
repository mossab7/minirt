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
	sphere.diameter = atof(data[2]);
	if (sphere.diameter <= 0)
	{
		ft_putstr_fd("Error: Invalid sphere diameter\n", 2);
		safe_exit(1);
	}
	sphere.color = get_color(data[3]);
	if (data[4])
		parse_pattern(&data[4], &sphere.pattern);
	else
		sphere.pattern.type = PATTERN_NONE;
	obj = alloc(sizeof(t_object));
	obj->type = SPHERE;
	obj->obj.sphere = sphere;
	container_push_back(scene->objects, obj);
}

void	parse_plane(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = PLANE;
	obj->obj.plane.center = get_vec3(data[1]);
	obj->obj.plane.normal = get_vec3(data[2]);
	check_vec_range(obj->obj.plane.normal);
	obj->obj.plane.color = get_color(data[3]);
	if (data[4])
		parse_pattern(&data[4], &obj->obj.plane.pattern);
	else
		obj->obj.plane.pattern.type = PATTERN_NONE;
	container_push_back(scene->objects, obj);
}

void	parse_cylinder(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->obj.cylinder.center = get_vec3(data[1]);
	obj->obj.cylinder.axis = get_vec3(data[2]);
	check_vec_range(obj->obj.cylinder.axis);
	obj->obj.cylinder.diameter = atof(data[3]);
	obj->obj.cylinder.height = atof(data[4]);
	obj->obj.cylinder.color = get_color(data[5]);
	if (data[6])
		parse_pattern(&data[6], &obj->obj.cylinder.pattern);
	else
		obj->obj.cylinder.pattern.type = PATTERN_NONE;
	container_push_back(scene->objects, obj);
}

void	parse_cone(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = CONE;
	obj->obj.cone.center = sub_vec3(get_vec3(data[1]),
			scale_vec3(obj->obj.cone.axis, obj->obj.cone.height));
	obj->obj.cone.axis = get_vec3(data[2]);
	check_vec_range(obj->obj.cone.axis);
	obj->obj.cone.diameter = atof(data[3]);
	obj->obj.cone.height = atof(data[4]);
	obj->obj.cone.color = get_color(data[5]);
	if (obj->obj.cone.diameter <= 0 || obj->obj.cone.height <= 0)
	{
		ft_putstr_fd("Error: Invalid cone diameter or height\n", 2);
		safe_exit(1);
	}
	if (data[6])
		parse_pattern(&data[6], &obj->obj.cone.pattern);
	else
		obj->obj.cone.pattern.type = PATTERN_NONE;
	container_push_back(scene->objects, obj);
}

void	parse_hyperboloid(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = HYPERBOLDOID;
	obj->obj.hyperboloid.center = get_vec3(data[1]);
	obj->obj.hyperboloid.axis = get_vec3(data[2]);
	check_vec_range(obj->obj.hyperboloid.axis);
	obj->obj.hyperboloid.diameter = atof(data[3]);
	obj->obj.hyperboloid.height = atof(data[4]);
	obj->obj.hyperboloid.color = get_color(data[5]);
	container_push_back(scene->objects, obj);
}
