/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasakh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:00:34 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/08 19:04:46 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdbool.h>
#include "../includes/transform_object.h"
#include "../includes/camera.h"
#define ROT_SPEED 0.1
#define TRANS_SPEED 0.5

void	trans_keys(int key, t_vec3 *trans, t_program *program, bool *changed)
{
	if (key == XK_Right)
		*trans = add_vec3(*trans,
				scale_vec3(program->scene->camera.right, TRANS_SPEED));
	if (key == XK_Left)
		*trans = add_vec3(*trans,
				scale_vec3(program->scene->camera.right, -TRANS_SPEED));
	if (key == XK_Up)
		*trans = add_vec3(*trans,
				scale_vec3(program->scene->camera.direction, TRANS_SPEED));
	if (key == XK_Down)
		*trans = add_vec3(*trans,
				scale_vec3(program->scene->camera.direction, -TRANS_SPEED));
	if (key == XK_space)
		*trans = add_vec3(*trans,
				scale_vec3(program->scene->camera.up, TRANS_SPEED));
	if (key == XK_Shift_L)
		*trans = add_vec3(*trans,
				scale_vec3(program->scene->camera.up, -TRANS_SPEED));
	if (key == XK_Down || key == XK_Up || key == XK_Left || key == XK_Right
		|| key == XK_Shift_L || key == XK_space)
		*changed = true;
}

void	rot_keys(int key, t_vec3 *rot, bool *has_changed)
{
	if (key == 'd')
		(*rot).y = ROT_SPEED;
	if (key == 'a')
		(*rot).y = -ROT_SPEED;
	if (key == 's')
		(*rot).x = ROT_SPEED;
	if (key == 'w')
		(*rot).x = -ROT_SPEED;
	if (key == 'e')
		(*rot).z = ROT_SPEED;
	if (key == 'q')
		(*rot).z = -ROT_SPEED;
	if (key == 'w' || key == 'a' || key == 's' || key == 'd' || key == 'q'
		|| key == 'e')
		*has_changed = true;
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
	program->scene->camera.position = add_vec3(
			program->scene->camera.position, trans);
	if (length_vec3(rotation) > 0)
	{
		rot_matrix = matrix4d_mult(rot_z, matrix4d_mult(rot_y, rot_x));
		program->scene->camera.direction = matrix4d_mult_vec3(
				rot_matrix, program->scene->camera.direction);
		program->scene->camera.direction = normalize_vec3(
				program->scene->camera.direction);
		recalculate_camera_vectors(&program->scene->camera);
	}
}

void	apply_transformation(t_program *program, t_vec3 trans, t_vec3 rot)
{
	if (program->selected_object.hit)
	{
		if (length_vec3(trans) > 0)
			translate_object(program->selected_object.object, trans);
		if (length_vec3(rot) > 0)
			rotate_object(program->selected_object.object, rot);
	}
	else
		transforme_camera(program, rot, trans);
	program->dirty = true;
}

int	key_hook(int keycode, void *param)
{
	t_program	*program;
	t_vec3		translation;
	t_vec3		rotation;
	bool		has_changed;

	program = (t_program *)param;
	translation = (t_vec3){0, 0, 0};
	rotation = (t_vec3){0, 0, 0};
	has_changed = false;
	if (keycode == XK_Escape)
	{
		if (program->selected_object.hit)
		{
			program->selected_object.hit = false;
			has_changed = true;
		}
		else
			safe_exit(0);
	}
	trans_keys(keycode, &translation, program, &has_changed);
	rot_keys(keycode, &rotation, &has_changed);
	if (has_changed)
		apply_transformation(program, translation, rotation);
	return (0);
}
