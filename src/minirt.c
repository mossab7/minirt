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

void 	safe_exit(int status)
{
	t_program	*program;

	program = *get_program();
	if (program->mlx && program->mlx->canvas->img_ptr)
		mlx_destroy_image(program->mlx->mlx_ptr, program->mlx->canvas->img_ptr);
	if (program->mlx && program->mlx->win_ptr)
		mlx_destroy_window(program->mlx->mlx_ptr, program->mlx->win_ptr);
	if (program->mlx && program->mlx->mlx_ptr)
		mlx_destroy_display(program->mlx->mlx_ptr);
	cleanup_memory_tracker(get_memory_tracker());
	exit(status);
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
	t_program 	*program;

	program = (t_program *)param;
	(void)program;
	// printf("--------------------------\n");
	// printf("Hit at distance: %f\n", program->selected_object.distance);
	// printf("Hit point: (%f, %f, %f)\n", program->selected_object.point.x, program->selected_object.point.y,
	// 		program->selected_object.point.z);
	// printf("Normal: (%f, %f, %f)\n", program->selected_object.normal.x, program->selected_object.normal.y,
	// 		program->selected_object.normal.z);
	// printf("Color: (%f, %f, %f)\n", program->selected_object.color.r, program->selected_object.color.g,
	// 		program->selected_object.color.b);
	// printf("--------------------------\n");
	
	return (0);
}

int key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307)
		safe_exit(0);
	return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
	t_program	*program;

	program = (t_program *)param;
	printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);
	t_vec3 screen_pos = screen_to_world(x, y);
	t_ray ray = shoot_ray((*get_program())->scene, screen_pos);
	t_hit_info hit_info = find_closest_intersection((*get_program())->scene->objects,
			&ray);
	(void)program;
	if (hit_info.hit)
	{
		// printf("Hit at distance: %f\n", hit_info.distance);
		// printf("Hit point: (%f, %f, %f)\n", hit_info.point.x, hit_info.point.y,
		// 	hit_info.point.z);
		// printf("Normal: (%f, %f, %f)\n", hit_info.normal.x, hit_info.normal.y,
		// 	hit_info.normal.z);
		// printf("Color: (%f, %f, %f)\n", hit_info.color.r, hit_info.color.g,
		// 	hit_info.color.b);
		// program->selected_object = hit_info;
	}

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
	render_scene(program);
	mlx_key_hook(program->mlx->win_ptr, key_hook, program);
	mlx_loop_hook(program->mlx->mlx_ptr, loop_hook, program);
	mlx_mouse_hook(program->mlx->win_ptr, mouse_hook, program);
	mlx_loop(program->mlx->mlx_ptr);
	safe_exit(0);
}
