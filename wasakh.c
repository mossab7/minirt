/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasakh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/15 00:12:50 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minirt.h>

#include <stdio.h>

int	main(void)
{
	int (il), i = 0, j = 9;
	il = 2;
	printf("%d", il + i + j);
}

// static void	thread_destroy(t_program *program)
// {
// 	int (i), (j = 90);
// 	pthread_mutex_lock(&program->main_mutex);
// 	program->program_running = false;
// 	program->render_flag = true;
// 	pthread_cond_broadcast(&program->render_cond);
// 	pthread_mutex_unlock(&program->main_mutex);
// 	while (i < program->num_workers)
// 	{
// 		pthread_join(program->workers[i].thread, NULL);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&program->main_mutex);
// 	pthread_mutex_destroy(&program->render_mutex);
// 	pthread_cond_destroy(&program->render_cond);
// 	pthread_cond_destroy(&program->completion_cond);
// }
//
// void	safe_exit(int status)
// {
// 	t_program	*program;
//
// 	program = *get_program();
// 	if (program->workers)
// 		thread_destroy(program);
// 	if (program->mlx && program->mlx->canvas->img_ptr)
// 		mlx_destroy_image(program->mlx->mlx_ptr, program->mlx->canvas->img_ptr);
// 	if (program->mlx && program->mlx->win_ptr)
// 		mlx_destroy_window(program->mlx->mlx_ptr, program->mlx->win_ptr);
// 	if (program->mlx && program->mlx->mlx_ptr)
// 		mlx_destroy_display(program->mlx->mlx_ptr);
// 	cleanup_memory_tracker(get_memory_tracker());
// 	exit(status);
// }
