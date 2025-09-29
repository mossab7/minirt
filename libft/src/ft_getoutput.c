/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getoutput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include <stdio.h>

int	run_command(char **argv, char **envp, int pipefd[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == CHILD_PROC)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		close(STDERR_FILENO);
		status = ft_execvpe(argv[0], argv, envp);
		exit(status);
	}
	else if (pid == ERROR)
		return (FAILIURE);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

char	*ft_getoutput(char **argv, char **envp)
{
	int		pipefd[2];
	char	*output;
	int		bytes_read;
	int		status;

	if (pipe(pipefd) == ERROR)
		return (NULL);
	status = run_command(argv, envp, pipefd);
	if (status != SUCCESS)
		return (NULL);
	output = malloc(PIPE_BUF + 1);
	if (output == NULL)
		return (NULL);
	bytes_read = read(pipefd[0], output, PIPE_BUF);
	if (bytes_read == ERROR)
		return (NULL);
	if (output[bytes_read - 1] == '\n')
		output[bytes_read - 1] = 0;
	else
		output[bytes_read] = 0;
	return (output);
}
/* 
 * 	TODO: give output as is without removing newline, the caller must handle
 *		the string as they wish
 * */
