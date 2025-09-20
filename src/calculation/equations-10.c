/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 01:26:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 03:04:43 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

#define KEY_COUNT 10

int	loop_hook(void *param)
{
	t_program (*program) = (t_program *)param;
	t_vec3 (translation) = (t_vec3){0, 0, 0};
	t_vec3 (rotation) = (t_vec3){0, 0, 0};
	bool (changed) = false;
	int (key), i;
	i = 0;
	while (i < KEY_COUNT)
	{
		key = get_keys()[i];
		if (program->keys[key])
		{
			trans_keys(key, &translation, program, &changed);
			rot_keys(key, &rotation, &changed);
		}
		i++;
	}
	if (changed)
		apply_transformation(program, translation, rotation);
	if (program->dirty)
	{
		render_scene(program);
		program->dirty = false;
	}
	return (0);
}

long	get_num_cores_unix(void)
{
	long	num_cores;

	num_cores = sysconf(_SC_NPROCESSORS_ONLN);
	if (num_cores > 0)
		return (num_cores);
	return (1);
}

void	set_single_worker_bounds(t_worker *worker)
{
	worker->start_x = 0;
	worker->end_x = WIN_WIDTH;
	worker->start_y = 0;
	worker->end_y = WIN_HEIGHT;
}

void	set_grid_division_bounds(t_worker *workers, int num_threads)
{
	int (sqrt_threads) = ((int)sqrt(num_threads));
	int (tiles_x) = sqrt_threads;
	int (tiles_y) = (num_threads + tiles_x - 1) / tiles_x;
	int (cols_per_tile) = WIN_WIDTH / tiles_x;
	int (rows_per_tile) = WIN_HEIGHT / tiles_y;
	int (i), tile_x, tile_y;
	i = 0;
	while (i < num_threads)
	{
		tile_x = i % tiles_x;
		tile_y = i / tiles_x;
		workers[i].start_x = tile_x * cols_per_tile;
		workers[i].start_y = tile_y * rows_per_tile;
		if (tile_x == tiles_x - 1)
			workers[i].end_x = WIN_WIDTH;
		else
			workers[i].end_x = (tile_x + 1) * cols_per_tile;
		if (tile_y == tiles_y - 1)
			workers[i].end_y = WIN_HEIGHT;
		else
			workers[i].end_y = (tile_y + 1) * rows_per_tile;
		i++;
	}
}

void	calculate_worker_bounds(t_program *program)
{
	t_worker (*workers) = program->workers;
	int (num_threads) = program->num_workers;
	if (num_threads == 1)
		set_single_worker_bounds(&workers[0]);
	else
		set_grid_division_bounds(workers, num_threads);
}
