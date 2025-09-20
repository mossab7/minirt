/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:59 by deepseeko         #+#    #+#             */
/*   Updated: 2025/09/20 03:14:12 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_keys(t_program *program)
{
	int (i) = 0;
	while (i < 7000)
	{
		program->keys[i] = false;
		i++;
	}
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
	set_keys(program);
	mlx_hook(program->mlx->win_ptr, 2, 1L << 0, key_press, program);
	mlx_hook(program->mlx->win_ptr, 3, 1L << 1, key_release, program);
	mlx_loop_hook(program->mlx->mlx_ptr, loop_hook, program);
	mlx_mouse_hook(program->mlx->win_ptr, mouse_hook, program);
	mlx_loop(program->mlx->mlx_ptr);
	safe_exit(0);
}
