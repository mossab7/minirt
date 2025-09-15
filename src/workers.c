/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:40:12 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 22:14:04 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	lock_wait(t_program *program, int *count)
{
	pthread_mutex_lock(&program->main_mutex);
	while ((!program->render_flag && program->program_running) || *count > 1)
	{
		pthread_cond_wait(&program->render_cond, &program->main_mutex);
		*count = 1;
	}
}

void	*worker_loop(void *arg)
{
	t_worker	*worker;
	t_program	*program;
	int			count;

	worker = (t_worker *)arg;
	program = worker->program;
	count = 1;
	while (1)
	{
		lock_wait(program, &count);
		if (!program->program_running)
		{
			pthread_mutex_unlock(&program->main_mutex);
			break ;
		}
		pthread_mutex_unlock(&program->main_mutex);
		worker_render_scene(worker);
		pthread_mutex_lock(&program->main_mutex);
		program->worker_finish_count++;
		if (program->worker_finish_count >= program->num_workers)
			pthread_cond_signal(&program->completion_cond);
		pthread_mutex_unlock(&program->main_mutex);
		count++;
	}
	return (NULL);
}

static void	init_worker_set_up(t_program *program, int num_threads,
		t_worker *workers)
{
	program->num_workers = num_threads;
	program->workers = workers;
	program->program_running = true;
	program->render_flag = false;
	program->worker_finish_count = 0;
	if (pthread_mutex_init(&program->main_mutex, NULL) != 0
		|| pthread_mutex_init(&program->render_mutex, NULL) != 0
		|| pthread_cond_init(&program->render_cond, NULL) != 0
		|| pthread_cond_init(&program->completion_cond, NULL) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize threading primitives\n", 2);
		safe_exit(1);
	}
}

void	set_up_workers(t_program *program)
{
	int			num_threads;
	t_worker	*workers;

	int (i) = 0;
	num_threads = get_num_cores_unix();
	workers = alloc(sizeof(t_worker) * num_threads);
	init_worker_set_up(program, num_threads, workers);
	calculate_worker_bounds(program);
	while (i < num_threads)
	{
		workers[i].program = program;
		if (pthread_create(&workers[i].thread, NULL, worker_loop,
				&workers[i]) != 0)
		{
			ft_putstr_fd("Error: Failed to create thread\n", 2);
			while (i >= 0)
			{
				pthread_cancel(workers[i].thread);
				pthread_join(workers[i].thread, NULL);
				i--;
			}
			safe_exit(1);
		}
		i++;
	}
}
