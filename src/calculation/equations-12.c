/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-12.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 01:31:57 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 01:33:39 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	initialize_threading_primitives(t_program *program)
{
	if (pthread_mutex_init(&program->main_mutex, NULL) != 0
		|| pthread_mutex_init(&program->render_mutex, NULL) != 0
		|| pthread_cond_init(&program->render_cond, NULL) != 0
		|| pthread_cond_init(&program->completion_cond, NULL) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize threading primitives\n", 2);
		safe_exit(1);
	}
}

static void	cancel_join_threads(t_worker *workers, int count)
{
	int (j) = 0;
	while (j < count)
	{
		pthread_cancel(workers[j].thread);
		pthread_join(workers[j].thread, NULL);
		j++;
	}
}

static void	create_worker_threads(t_program *program,
		t_worker *workers, int num_threads)
{
	int (i) = 0;
	while (i < num_threads)
	{
		workers[i].program = program;
		if (pthread_create(&workers[i].thread,
				NULL, worker_loop, &workers[i]) != 0)
		{
			ft_putstr_fd("Error: Failed to create thread\n", 2);
			cancel_join_threads(workers, i);
			safe_exit(1);
		}
		i++;
	}
}

void	set_up_workers(t_program *program)
{
	int			num_threads;
	t_worker	*workers;

	num_threads = get_num_cores_unix();
	workers = alloc(sizeof(t_worker) * num_threads);
	program->num_workers = num_threads;
	program->workers = workers;
	program->program_running = true;
	program->render_flag = false;
	program->worker_finish_count = 0;
	initialize_threading_primitives(program);
	calculate_worker_bounds(program);
	create_worker_threads(program, workers, num_threads);
}
