/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:44:01 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:57:49 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_container	*read_file_lines(int fd)
{
	t_str		*line;
	t_str		tmp;
	t_container	*lines_list;

	t_str (file) = read_file_fd(fd);
	size_t (start) = 0;
	if (!file.size)
		return (str_destroy(&file),
			set_error(9, "Empty file"), print_error(), safe_exit(9), NULL);
	lines_list = container_init();
	while (str_peek(&file))
	{
		if (str_peek(&file) == '\n' || !str_peek(&file))
		{
			tmp = str_substr(&file, start, file.peek - start);
			line = malloc(sizeof(t_str));
			if (!line)
				safe_exit(-1);
			*line = tmp;
			container_push_back(lines_list, line);
			start = file.peek + 1;
		}
		str_peek_advance(&file);
	}
	return (str_destroy(&file), lines_list);
}

t_parse_entry	*parse_entry(void)
{
	static t_parse_entry	parsers[] = {
	{"A", parse_ambient, 1},
	{"C", parse_camera, 1},
	{"L", parse_light, 1},
	{"sp", parse_sphere, 2},
	{"pl", parse_plane, 2},
	{"cy", parse_cylinder, 2},
	{"co", parse_cone, 2},
	{NULL, NULL, 0}
	};

	return (parsers);
}

void	check_occ(t_str id)
{
	static size_t	occ[2] = {0, 0};

	if (!id.data)
	{
		if (occ[0] == 0)
			set_error(5, "Missing element : [Ambiant]");
		if (occ[1] == 0)
			set_error(5, "Missing element : [Camera]");
		return ;
	}
	if (str_match(&id, "A", ft_strncmp, 0))
	{
		occ[0]++;
		if (occ[0] > 1)
			set_error(5, "Repeated element : [Ambiant]");
		return ;
	}
	else if (str_match(&id, "C", ft_strncmp, 0))
	{
		occ[1]++;
		if (occ[1] > 1)
			set_error(5, "Repeated element : [Camera]");
		return ;
	}
}
