/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 01:36:59 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:58:12 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	parse_line(t_scene *scene, t_str *line)
{
	t_str				id;
	const t_parse_entry	*parsers = parse_entry();

	int (i) = 0;
	id = extract_identifier(line);
	check_occ(id);
	if (get_error_system()->code)
		return ;
	while (parsers[i].key)
	{
		if (str_match(line, parsers[i].key, ft_strncmp, 0)
			&& parsers[i].len == id.size)
		{
			parsers[i].fn(scene, line);
			str_destroy(&id);
			return ;
		}
		i++;
	}
	str_destroy(&id);
	if (line->data[0])
		set_error(4, "Unkown identifier : [%s]", line->data);
}

void	read_scene(int fd, t_scene *scene)
{
	t_container	*file_content;
	size_t		i;
	t_str		*line;

	file_content = read_file_lines(fd);
	i = 0;
	while (i < file_content->size)
	{
		parse_line(scene, ((t_str *)((void **)file_content->data)[i]));
		str_destroy(((t_str *)((void **)file_content->data)[i]));
		free(((void **)file_content->data)[i]);
		if (get_error_system()->code != 0)
		{
			append_error_detail(" : line %zu", i + 1);
			while (++i < file_content->size)
			{
				line = (t_str *)((void **)file_content->data)[i];
				str_destroy(line);
				free(line);
			}
			return ;
		}
		i++;
	}
	check_occ((t_str){NULL, 0, 0, 0});
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)alloc(sizeof(t_scene));
	scene->objects = container_init();
	scene->lights = container_init();
	return (scene);
}

int	parse_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 3 || ft_strcmp(filename + len - 3, ".rt") != 0)
		return (-1);
	return (0);
}

void	parse_scene(char *filename, t_scene	*scene)
{
	int		fd;

	if (parse_filename(filename) == -1)
	{
		ft_putstr_fd("Error: Invalid file name\n", 2);
		safe_exit(1);
	}
	fd = ft_open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Invalid file name\n", 2);
		safe_exit(1);
	}
	read_scene(fd, scene);
	if (get_error_system()->code != 0)
		return ;
	ft_close((void *)(intptr_t)fd);
	return ;
}
