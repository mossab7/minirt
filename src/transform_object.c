/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 23:28:53 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/17 17:27:54 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/transform_object.h"

void	translate_object(t_object *obj, t_vec3 translation)
{
	if (!obj)
		return ;
	if (obj->type == SPHERE)
		obj->obj.sphere.center = add_vec3(obj->obj.sphere.center, translation);
	else if (obj->type == PLANE)
		obj->obj.plane.center = add_vec3(obj->obj.plane.center, translation);
	else if (obj->type == CYLINDER)
		obj->obj.cylinder.center = add_vec3(obj->obj.cylinder.center,
				translation);
	else if (obj->type == CONE)
		obj->obj.cone.center = add_vec3(obj->obj.cone.center, translation);
}

static t_matrix4d	rot_mat(t_vec3 rotation_angles)
{
	t_matrix4d	rot_x;
	t_matrix4d	rot_y;
	t_matrix4d	rot_z;

	rot_x = matrix4d_rotation_x(rotation_angles.x);
	rot_y = matrix4d_rotation_y(rotation_angles.y);
	rot_z = matrix4d_rotation_z(rotation_angles.z);
	return (matrix4d_mult(rot_z, matrix4d_mult(rot_y, rot_x)));
}

void	rotate_object(t_object *obj, t_vec3 rotation_angles)
{
	t_matrix4d	rot_matrix;
	t_vec3		*axis;

	if (!obj)
		return ;
	rot_matrix = rot_mat(rotation_angles);
	axis = NULL;
	if (obj->type == PLANE)
		axis = &obj->obj.plane.normal;
	else if (obj->type == CYLINDER)
		axis = &obj->obj.cylinder.axis;
	else if (obj->type == CONE)
		axis = &obj->obj.cone.axis;
	else if (obj->type == SPHERE)
		return ;
	if (axis)
	{
		*axis = matrix4d_mult_vec3(rot_matrix, *axis);
		*axis = normalize_vec3(*axis);
	}
}

void	recalculate_camera_vectors(t_camera *camera)
{
	camera->right = normalize_vec3(cross_vec3(camera->direction, UPVEC));
	camera->up = normalize_vec3(cross_vec3(camera->direction, camera->right));
	camera->right = normalize_vec3(cross_vec3(camera->direction, camera->up));
}

void	transforme_camera(t_program *program, t_vec3 rotation, t_vec3 trans)
{
	t_matrix4d	rot_matrix;
	t_matrix4d	rot_x;
	t_matrix4d	rot_y;
	t_matrix4d	rot_z;

	rot_x = matrix4d_rotation_x(rotation.x);
	rot_y = matrix4d_rotation_y(rotation.y);
	rot_z = matrix4d_rotation_z(rotation.z);
	program->scene->camera.position = add_vec3(program->scene->camera.position,
			trans);
	if (length_vec3(rotation) > 0)
	{
		rot_matrix = matrix4d_mult(rot_z, matrix4d_mult(rot_y, rot_x));
		program->scene->camera.direction = matrix4d_mult_vec3(rot_matrix,
				program->scene->camera.direction);
		program->scene->camera.direction = normalize_vec3(program->scene->camera.direction);
		recalculate_camera_vectors(&program->scene->camera);
	}
}
