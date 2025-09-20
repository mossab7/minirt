/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:08:52 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/18 17:11:38 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	parse_paraboloid(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	handle_allocation_failure(obj);
	register_memory_allocation(get_memory_tracker(),
		create_memory_record(obj, free_object));
	obj->type = PARABOLOID;
	obj->obj.paraboloid.center = get_vec3(data[1]);
	obj->obj.paraboloid.axis = get_vec3(data[2]);
	check_vec_range(obj->obj.paraboloid.axis);
	obj->obj.paraboloid.diameter = atof(data[3]);
	obj->obj.paraboloid.height = atof(data[4]);
	obj->obj.paraboloid.color = get_color(data[5]);
	container_push_back(scene->objects, obj);
}

void	read_to_scene(int fd, t_scene *scene)
{
	char	*line;
	char	**data;
	size_t	len;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '#' || line[0] == '\n' || ft_strlen(line) <= 1)
		{
			ft_free(line);
			continue ;
		}
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		data = ft_split(line, ' ');
		if (data && data[0])
			parse_obj_data(data, scene);
		ft_free_2d(data, -1);
		ft_free(line);
	}
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)alloc(sizeof(t_scene));
	scene->objects = container_init();
	scene->lights = container_init();
	return (scene);
}

t_scene	*parse_scene(char *filename)
{
	t_scene	*scene;
	int		fd;

	if (parse_filename(filename) == -1)
	{
		ft_putstr_fd("Error: Invalid file name\n", 2);
		safe_exit(1);
	}
	scene = init_scene();
	fd = ft_open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Invalid file name\n", 2);
		safe_exit(1);
	}
	read_to_scene(fd, scene);
	ft_close((void *)(intptr_t)fd);
	return (scene);
}
