/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:59 by deepseeko         #+#    #+#             */
/*   Updated: 2025/10/01 18:40:45 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_keys(t_program *program)
{
	int (i) = 0;
	while (i < 70000)
	{
		program->keys[i] = false;
		i++;
	}
}

int	cross_exit(void *param)
{
	(void)param;
	safe_exit(0);
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
	program->mlx = _init_mlx();
	program->scene = init_scene();
	parse_scene(argv[1], program->scene);
	if (get_error_system()->code != 0)
		return (print_error(), safe_exit(get_error_system()->code));
	set_up_workers(program);
	render_scene(program);
	program->dirty = true;
	set_keys(program);
	mlx_hook(program->mlx->win_ptr, 2, 1L << 0, key_press, program);
	mlx_hook(program->mlx->win_ptr, 3, 1L << 1, key_release, program);
	mlx_hook(program->mlx->win_ptr, 17, 0, cross_exit, program);
	mlx_loop_hook(program->mlx->mlx_ptr, loop_hook, program);
	mlx_mouse_hook(program->mlx->win_ptr, mouse_hook, program);
	mlx_loop(program->mlx->mlx_ptr);
	safe_exit(0);
}
