/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:26:54 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 03:09:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <transform_object.h>

#define ROT_SPEED 0.1
#define TRANS_SPEED 3
#define UP 65362
#define K_DOWN 'k'
#define K_LEFT 'j'
#define K_RIGHT 'l'
#define K_SHIFT 'o'
#define K_SPACE 'u'

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
	{
		*changed = true;
	}
}

void	rot_keys(int key, t_vec3 *rot, bool *has_changed)
{
	if (key == 'd')
		(*rot).y = ROT_SPEED;
	if (key == 'a')
		(*rot).y = -ROT_SPEED;
	if (key == 'w')
		(*rot).x = ROT_SPEED;
	if (key == 's')
		(*rot).x = -ROT_SPEED;
	if (key == 'e')
		(*rot).z = ROT_SPEED;
	if (key == 'q')
		(*rot).z = -ROT_SPEED;
	if (key == 'w' || key == 'a' || key == 's' || key == 'd' || key == 'q'
		|| key == 'e')
		*has_changed = true;
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

int	mouse_hook(int button, int x, int y, void *param)
{
	t_program	*program;

	(void)button;
	program = (t_program *)param;
	t_vec3 (screen_pos) = screen_to_world(x, y);
	t_ray (ray) = shoot_ray((*get_program())->scene, screen_pos);
	t_hit_info (hit_info) = find_closest_intersection(
		(*get_program())->scene->objects, &ray);
	(void)program;
	if (hit_info.hit)
		program->selected_object = hit_info;
	else
		program->selected_object.hit = false;
	program->dirty = true;
	return (0);
}
