/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 01:36:59 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/28 23:01:32 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include "ft_string.h"
#include <X11/Xlib.h>
#include <minirt.h>
#include <stddef.h>
#include <stdio.h>

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

void	print_ambiant(const t_amb_light *ambiant)
{
	if (!ambiant)
		return ;
	printf(COLOR_CYAN "Ambiant infos : " COLOR_RESET
		"ratio=[%f] | color=[%f][%f][%f]\n",
		ambiant->ratio,
		ambiant->color.r, ambiant->color.g, ambiant->color.b);
}

void	print_camera(const t_camera *cam)
{
	if (!cam)
		return ;
	printf(COLOR_CYAN "Camera infos : " COLOR_RESET
		"pos=[%f][%f][%f] | normalvec=[%f][%f][%f] | fov=[%f]\n",
		cam->position.x, cam->position.y, cam->position.z,
		cam->direction.x, cam->direction.y, cam->direction.z,
		cam->fov);
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
	print_ambiant(&scene->amb_light);
	print_camera(&scene->camera);

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

void	end_of_line_parse(t_str *fields, size_t fields_count, size_t start)
{
	while (++start < fields_count)
	{
		str_peek_reset(&fields[start]);
		while (str_peek(&fields[start]) && str_peek(&fields[start]) == ' ')
			str_peek_advance(&fields[start]);
		if (str_peek(&fields[start]) && str_peek(&fields[start]) != ' ')
		{
			set_error(3, "Unexpexted format");
			return ;
		}
	}
}

void	parse_ambient(t_scene *scene, t_str *line)
{
	size_t	count;
	t_str	*fields;

	(void)scene;
	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	scene->amb_light.ratio = extract_ratio(&fields[1]);
	scene->amb_light.color = extract_color(&fields[2]);
	end_of_line_parse(fields ,count, 2);
	if (get_error_system()->code)
	{
		append_error_detail(" in Ambiant");
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
}

double	dgree_to_rad(double degree)
{
	return ((degree * M_PI) / 180.0);
}

void	parse_camera(t_scene *scene, t_str *line)
{
	size_t	count;
	t_str	*fields;

	str_peek_reset(line);
	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	scene->camera.position = extract_vec3(&fields[1]);
	scene->camera.direction = extract_normalvec(&fields[2]);
	scene->camera.fov = extract_fov(&fields[3]);
	end_of_line_parse(fields, count, 3);
	if (get_error_system()->code)
	{
		append_error_detail(" in Camera");
		str_free_array(fields, count);
		return ;
	}
	scene->camera.direction = add_vec3(scene->camera.direction,
			(t_vec3){EPSILON, EPSILON, EPSILON});
	scene->camera.direction = normalize_vec3(scene->camera.direction);
	scene->camera.width = tan(dgree_to_rad(scene->camera.fov / 2));
	scene->camera.height = scene->camera.width / (16.0f / 9.0f);
	str_free_array(fields, count);
	recalculate_camera_vectors(&scene->camera);
}

void	parse_light(t_scene *scene, t_str *line)
{
	size_t	count;
	t_str	*fields;
	t_light	*light;

	light = (t_light *)alloc(sizeof(t_light));
	str_peek_reset(line);
	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	light->position = extract_vec3(&fields[1]);
	light->intensity = extract_ratio(&fields[2]);
	light->color = extract_color(&fields[3]);
	end_of_line_parse(fields, count, 3);
	if (get_error_system()->code)
	{
		append_error_detail(" in Light");
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->lights, light);
}

static void	fill_sphere(t_sphere *sphere, t_str *fields)
{
	sphere->center = extract_vec3(&fields[1]);
	sphere->diameter = extract_diameter(&fields[2]);
	sphere->color = extract_color(&fields[3]);
}

void	parse_sphere(t_scene *scene, t_str *line)
{
	size_t		count;
	t_str		*fields;
	t_object	*object;
	t_sphere	sphere;

	str_peek_reset(line);
	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	fill_sphere(&sphere, fields);
	if (get_error_system()->code != 0)
	{
		str_free_array(fields, count);
		return ;
	}
	object = alloc(sizeof(t_object));
	if (count > 4)
		extract_pattern(fields, &object->pattern, count, 4);
	else
		object->pattern.type = PATTERN_NONE;
	if (get_error_system()->code != 0)
	{
		append_error_detail(" in sphere");
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	object->type = SPHERE;
	object->u_obj.sphere = sphere;
	container_push_back(scene->objects, object);
}

void	parse_plane(t_scene *scene, t_str *line)
{
	t_object	*obj;
	t_str		*fields;
	size_t		count;

	fields = str_split(line, ' ', &count);
	obj = alloc(sizeof(t_object));
	obj->type = PLANE;
	obj->u_obj.plane.center = extract_vec3(&fields[1]);
	obj->u_obj.plane.normal = extract_vec3(&fields[2]);
	obj->u_obj.plane.color = extract_color(&fields[3]);
	if (count > 4)
		extract_pattern(fields, &obj->pattern, count, 4);
	else
		obj->pattern.type = PATTERN_NONE;
	if (get_error_system()->code != 0)
	{
		append_error_detail(" in plane");
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->objects, obj);
}

void	parse_cylinder(t_scene *scene, t_str *line)
{
	t_object	*obj;
	t_str		*fields;
	size_t		count;
	
	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	obj = alloc(sizeof(t_object));
	obj->type = CYLINDER;   
	obj->u_obj.cylinder.center = extract_vec3(&fields[1]);
	obj->u_obj.cylinder.axis = extract_vec3(&fields[2]);
	obj->u_obj.cylinder.diameter = ft_atof(fields[3].data);
	obj->u_obj.cylinder.height = ft_atof(fields[4].data);
	obj->u_obj.cylinder.color = extract_color(&fields[5]);
	if (count > 6)
		extract_pattern(fields, &obj->pattern, count, 6);
	else
		obj->pattern.type = PATTERN_NONE;
	if (get_error_system()->code != 0)
	{
		append_error_detail(" in cylinder");
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->objects, obj);
}

void	parse_cone(t_scene *scene, t_str *line)
{
	t_object	*obj;
	t_str		*fields;
	size_t		count;

	fields = str_split(line, ' ', &count);
	if (count < 6)
		set_error(9, "Missing fields");
	obj = alloc(sizeof(t_object));
	obj->type = CONE;
	obj->u_obj.cone.center = sub_vec3(extract_vec3(&fields[1]),
			scale_vec3(obj->u_obj.cone.axis, obj->u_obj.cone.height));
	obj->u_obj.cone.axis = extract_vec3(&fields[2]);
	obj->u_obj.cone.diameter = ft_atof(fields[3].data);
	obj->u_obj.cone.height = ft_atof(fields[4].data);
	obj->u_obj.cone.color = extract_color(&fields[5]);
	obj->pattern.type = PATTERN_NONE;
	if (count > 6)
		extract_pattern(fields, &obj->pattern, count, 6);
	if (get_error_system()->code)
	{
		append_error_detail(" in cone");
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
	container_push_back(scene->objects, obj);
}

static	t_parse_entry	*parse_entry(void)
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
			return ;
		}
		i++;
	}
	if (line->data[0])
	set_error(4, "Unkown identifier : [%s]", line->data);
}

void	read_scene(int fd, t_scene *scene)
{
	t_container	*file_content;
	size_t		i;

	file_content = read_file_lines(fd);
	i = 0;
	while (i < file_content->size)
	{
		parse_line(scene, ((t_str *)((void **)file_content->data)[i]));
		if (get_error_system()->code != 0)
		{
			append_error_detail(" : line %zu", i + 1);
			return ;
		}
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

// void	pri

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
	if (get_error_system()->code != 0)
		return (NULL);
	// print_scene(scene);
	ft_close((void *)(intptr_t)fd);
	return (scene);
}

static void	set_keys(t_program *program)
{
	int (i) = 0;
	while (i < 70000)
	{
		program->keys[i] = false;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	program = *get_program();
	program->mlx = _init_mlx();
	// program->scene = parse_scene(argv[1]);
	program->scene = parse_scene(argv[1]);
	if (get_error_system()->code != 0)
	{
		print_error();
		return (get_error_system()->code);
	}
	set_up_workers(program);
	render_scene(program);
	program->dirty = true;
	set_keys(program);
	mlx_hook(program->mlx->win_ptr, 2, 1L << 0, key_press, program);
	mlx_hook(program->mlx->win_ptr, 3, 1L << 1, key_release, program);
	mlx_hook(program->mlx->win_ptr, 17, 0, safe_exit, program);
	mlx_loop_hook(program->mlx->mlx_ptr, loop_hook, program);
	mlx_mouse_hook(program->mlx->win_ptr, mouse_hook, program);
	mlx_loop(program->mlx->mlx_ptr);
	safe_exit(0);
}
