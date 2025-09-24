/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

static int	get_status(void)
{
	if (errno == EACCES || errno == EISDIR)
		return (NON_EXEC);
	return (CMD_NOT_FOUND);
}

static int	execute_file(char **path_list, char *file, char **av, char **envp)
{
	char	*file_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		file_path = ft_strjoin(path_list[i++], file);
		if (file_path == NULL)
			return (ERROR);
		execve(file_path, av, envp);
		free(file_path);
	}
	return (get_status());
}

int	ft_execvpe(char *file, char **av, char **envp)
{
	char	*path;
	char	**path_list;
	int		status;

	if (ft_strchr(file, '/') && execve(file, av, envp) == ERROR)
		return (get_status());
	path = ft_getenv(envp, "PATH=");
	if (path == NULL && execve(file, av, envp) == ERROR)
		return (get_status());
	path_list = ft_getpath(path);
	if (path_list == NULL)
		return (ERROR);
	status = execute_file(path_list, file, av, envp);
	ft_free_vector(path_list);
	return (status);
}
