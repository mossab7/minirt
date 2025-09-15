/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:34:45 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 21:58:33 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_single_worker_bounds(t_worker *worker)
{
	worker->start_x = 0;
	worker->end_x = WIN_WIDTH;
	worker->start_y = 0;
	worker->end_y = WIN_HEIGHT;
}

void	set_grid_division_bounds(t_worker *workers, int num_threads)
{
	int	tiles_x;

	int (i), (tile_x), (tile_y), (rows_per_tile), (cols_per_tile), (tiles_y);
	tiles_x = (int)sqrt(num_threads);
	tiles_y = (num_threads + tiles_x - 1) / tiles_x;
	cols_per_tile = WIN_WIDTH / tiles_x;
	rows_per_tile = WIN_HEIGHT / tiles_y;
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
	int			num_threads;
	t_worker	*workers;

	num_threads = program->num_workers;
	workers = program->workers;
	if (num_threads == 1)
		set_single_worker_bounds(&workers[0]);
	else
		set_grid_division_bounds(workers, num_threads);
}
