/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:59 by deepseeko         #+#    #+#             */
/*   Updated: 2025/09/14 22:13:55 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"
#include "../includes/transform_object.h"
#include <X11/keysym.h>
#include <minirt.h>

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

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	program = *get_program();
	program->mlx = _init_mlx();
	program->scene = parse_scene(argv[1]);
	set_up_workers(program);
	render_scene(program);
	program->dirty = true;
	mlx_key_hook(program->mlx->win_ptr, key_hook, program);
	mlx_loop_hook(program->mlx->mlx_ptr, loop_hook, program);
	mlx_mouse_hook(program->mlx->win_ptr, mouse_hook, program);
	mlx_loop(program->mlx->mlx_ptr);
	safe_exit(0);
}
