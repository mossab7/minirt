/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 01:36:59 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/24 02:30:31 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

char *get_type(t_object_type type)
{
    if (type == SPHERE)
        return ("SPHERE");
    else if (type == PLANE)
        return ("PLANE");
    else if (type == CYLINDER)
        return ("CYLINDER");
    else if (type == HYPERBOLDOID)
        return ("HYPERBOLDOID");
    else if (type == PARABOLOID)
        return ("PARABOLOID");
    return ("UNKNOWN");
}

void print_sphere(t_object *obj)
{
    t_sphere *sphere = &obj->u_obj.sphere;
    printf("Sphere: Center: (%f, %f, %f), Diameter: %f\n",
           sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter);
    printf ("Color: (%f, %f, %f)\n", sphere->color.r, sphere->color.g, sphere->color.b);
}

void print_plane(t_object *obj)
{
    t_plane *plane = &obj->u_obj.plane;
    printf("Plane: Center: (%f, %f, %f), Normal: (%f, %f, %f)\n",
           plane->center.x, plane->center.y, plane->center.z,
           plane->normal.x, plane->normal.y, plane->normal.z);
    printf ("Color: (%f, %f, %f)\n", plane->color.r, plane->color.g, plane->color.b);
}
void print_cylinder(t_object *obj)
{
    t_cylinder *cylinder = &obj->u_obj.cylinder;
    printf("Cylinder: Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f, Height: %f\n",
           cylinder->center.x, cylinder->center.y, cylinder->center.z,
           cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
           cylinder->diameter, cylinder->height);
    printf ("Color: (%f, %f, %f)\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
}
void print_hyperboloid(t_object *obj)
{
    t_hyperboloid *hyperboloid = &obj->u_obj.hyperboloid;
    printf("Hyperboloid: Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f, Height: %f\n",
           hyperboloid->center.x, hyperboloid->center.y, hyperboloid->center.z,
           hyperboloid->axis.x, hyperboloid->axis.y, hyperboloid->axis.z,
           hyperboloid->diameter, hyperboloid->height);
    printf ("Color: (%f, %f, %f)\n", hyperboloid->color.r, hyperboloid->color.g, hyperboloid->color.b);
}
void print_paraboloid(t_object *obj)
{
    t_paraboloid *paraboloid = &obj->u_obj.paraboloid;
    printf("Paraboloid: Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f\n",
           paraboloid->center.x, paraboloid->center.y, paraboloid->center.z,
           paraboloid->axis.x, paraboloid->axis.y, paraboloid->axis.z,
           paraboloid->diameter);
    printf ("Color: (%f, %f, %f)\n", paraboloid->color.r, paraboloid->color.g, paraboloid->color.b);
}
void print_object(t_object *obj)
{
    if (obj->type == SPHERE)
        print_sphere(obj);
    else if (obj->type == PLANE)
        print_plane(obj);
    else if (obj->type == CYLINDER)
        print_cylinder(obj);
    else if (obj->type == HYPERBOLDOID)
        print_hyperboloid(obj);
    else if (obj->type == PARABOLOID)
        print_paraboloid(obj);
}

void print_scene(t_scene *scene)
{
    for(size_t i = 0; i < scene->objects->size; i++)
    {
        t_object *obj = get_object(scene->objects, i);
        if (obj)
        {
            printf("Object %zu: Type: %s\n", i, get_type(obj->type));
            print_object(obj);
            printf("\n");
        }
    }
}

t_container	*read_file_lines(int fd)
{
	t_str	file;
	t_str	*line;
	t_str	tmp;
	t_container	*lines_list;
	size_t	start;

	file = read_file_fd(fd);
	lines_list = container_init();
	start = 0;
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

static	t_parse_entry	*parse_entry(void)
{
	static t_parse_entry	parsers[] = {
	{"A", parse_ambient, 1},
	{"C", parse_camera, 1},
	{"L", parse_light, 1},
	{"pl", parse_plane, 2},
	{"sp", parse_sphere, 2},
	{"cy", parse_cylinder, 2},
	{NULL, NULL, 0}
	};

	return (parsers);
}
void	read_scene(int fd, t_scene *scene)
{
	t_container	*file_content;
	size_t		i;

	file_content = read_file_lines(fd);
	i = 0;
	while (i < file_content->size)
	{
		printf("%s\n", ((t_str *)((void **)file_content->data)[i])->data);
		i++;
	}
	(void)scene;
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

	// if (parse_filename(filename) == -1)
	// {
	// 	ft_putstr_fd("Error: Invalid file name\n", 2);
	// 	safe_exit(1);
	// }
	scene = init_scene();
	fd = ft_open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Invalid file name\n", 2);
		safe_exit(1);
	}
	read_scene(fd, scene);
	ft_close((void *)(intptr_t)fd);
	return (scene);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	t_program	*program = *get_program();
	program->scene = parse_scene(av[1]);
}
