/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:59 by deepseeko         #+#    #+#             */
/*   Updated: 2025/07/12 19:03:00 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include "../includes/transform_object.h"
#include "../includes/camera.h"

t_program	**get_program(void)
{
	static t_program	*program;

	if (!program)
	{
		program = alloc(sizeof(t_program));
		program->scene = NULL;
		program->mlx = NULL;
	}
	return (&program);
}

void	destroy_window(void *ptr)
{
	t_program	*program;

	(void)ptr;
	program = *get_program();
	mlx_destroy_window(program->mlx->mlx_ptr, program->mlx->win_ptr);
}

void	destroy_image(void *ptr)
{
	t_program	*program;

	(void)ptr;
	program = *get_program();
	mlx_destroy_image(program->mlx->mlx_ptr, program->mlx->canvas->img_ptr);
}

t_object	*get_object(t_container *container, size_t index)
{
	t_object	*obj;

	if (index >= container->size)
		return (NULL);
	obj = ((t_object **)container->data)[index];
	return (obj);
}

void	register_allocation(void *ptr, void (*free_func)(void *))
{
	register_memory_allocation(get_memory_tracker(), create_memory_record(ptr,
			free_func));
}

t_canvas	*init_canvas(void *mlx_ptr, int width, int height)
{
	t_canvas	*canvas;

	canvas = alloc(sizeof(t_canvas));
	canvas->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!canvas->img_ptr)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		safe_exit(1);
	}
	canvas->addr = mlx_get_data_addr(canvas->img_ptr, &canvas->bpp,
			&canvas->line_length, &canvas->endian);
	return (canvas);
}

t_mlx	*_init_mlx(void)
{
	t_mlx	*mlx;

	mlx = alloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		ft_putstr_fd("Error: Failed to initiate mlx connection\n", 2);
		safe_exit(1);
	}
	register_allocation(mlx->mlx_ptr, free);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"MiniRT");
	if (!mlx->win_ptr)
	{
		ft_putstr_fd("Error: Failed to create window\n", 2);
		safe_exit(1);
	}
	mlx->canvas = init_canvas(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	return (mlx);
}

int loop_hook(void *param)
{
	t_program *program = (t_program *)param;

	if (program->dirty)
	{
		render_scene(program);
		program->dirty = false;
	}
	return (0);
}

int key_hook(int keycode, void *param)
{
	t_program *program = (t_program *)param;
	t_vec3 translation = {0, 0, 0};
	t_vec3 rotation = {0, 0, 0};
	double trans_speed = 0.5;
	double rot_speed = 0.1;
	bool has_changed = false;

	if (keycode == 65307) // ESC
	{
		if (program->selected_object.hit)
		{
			program->selected_object.hit = false;
			has_changed = true;
		}
		else
			safe_exit(0);
	}
	if (keycode == 32) { translation.y = trans_speed; has_changed = true; } // Space -> Up
	if (keycode == 65505) { translation.y = -trans_speed; has_changed = true; } // L-Shift -> Down
	if (keycode == 65361) { translation.x = trans_speed; has_changed = true; } // Left
	if (keycode == 65363) { translation.x = -trans_speed; has_changed = true; } // Right
	if (keycode == 65362) { translation.z = trans_speed; has_changed = true; } // Arrow Up -> Depth In
	if (keycode == 65364) { translation.z = -trans_speed; has_changed = true; } // Arrow Down -> Depth Out
	if (keycode == 'a') { rotation.y = rot_speed; has_changed = true; }
	if (keycode == 'd') { rotation.y = -rot_speed; has_changed = true; }
	if (keycode == 'w') { rotation.x = rot_speed; has_changed = true; }
	if (keycode == 's') { rotation.x = -rot_speed; has_changed = true; }
	if (keycode == 'q') { rotation.z = rot_speed; has_changed = true; }
	if (keycode == 'e') { rotation.z = -rot_speed; has_changed = true; }
	if (has_changed)
	{
		if (program->selected_object.hit)
		{
			if (length_vec3(translation) > 0)
				translate_object(program->selected_object.object, translation);
			if (length_vec3(rotation) > 0)
				rotate_object(program->selected_object.object, rotation);
		}
		else
		{
			t_matrix4d rot_matrix;
			t_matrix4d rot_x = matrix4d_rotation_x(rotation.x);
			t_matrix4d rot_y = matrix4d_rotation_y(rotation.y);
			t_matrix4d rot_z = matrix4d_rotation_z(rotation.z);
			program->scene->camera.position = add_vec3(program->scene->camera.position, translation);
			if (length_vec3(rotation) > 0)
			{
				rot_matrix = matrix4d_mult(rot_z, matrix4d_mult(rot_y, rot_x));
				program->scene->camera.direction = matrix4d_mult_vec3(rot_matrix, program->scene->camera.direction);
				program->scene->camera.direction = normalize_vec3(program->scene->camera.direction);
				recalculate_camera_vectors(&program->scene->camera);
			}
		}
        program->dirty = true;
	}
	return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
	t_program	*program;

	(void)button;
	program = (t_program *)param;
	t_vec3 screen_pos = screen_to_world(x, y);
	t_ray ray = shoot_ray((*get_program())->scene, screen_pos);
	t_hit_info hit_info = find_closest_intersection((*get_program())->scene->objects,
			&ray);
	if (hit_info.hit)
		program->selected_object = hit_info;
	else
		program->selected_object.hit = false;
    program->dirty = true;
	return (0);
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
	program->scene = parse_scene(argv[1]);
	program->mlx = _init_mlx();
	program->dirty = true;
	mlx_key_hook(program->mlx->win_ptr, key_hook, program);
	mlx_loop_hook(program->mlx->mlx_ptr, loop_hook, program);
	mlx_mouse_hook(program->mlx->win_ptr, mouse_hook, program);
	mlx_loop(program->mlx->mlx_ptr);
	safe_exit(0);
}

