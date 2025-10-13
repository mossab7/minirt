/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:12:30 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/24 17:40:08 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

t_str	read_file(const char *file_name)
{
	t_str	file;
	t_str	tmp;
	int		fd;

	str_init(&file);
	fd = open(file_name, O_RDONLY);
	tmp = str_from_cstr(get_next_line(fd));
	while (tmp.data)
	{
		str_append(&file, tmp.data);
		str_destroy(&tmp);
		tmp = str_from_cstr(get_next_line(fd));
	}
	return (file);
}

t_str	read_file_fd(int fd)
{
	t_str	file;
	t_str	tmp;
	char	*line;

	str_init(&file);
	line = get_next_line(fd);
	tmp = str_from_cstr(line);
	while (tmp.data)
	{
		str_append(&file, tmp.data);
		free(line);
		str_destroy(&tmp);
		line = get_next_line(fd);
		tmp = str_from_cstr(line);
	}
	free(line);
	str_destroy(&tmp);
	return (file);
}
