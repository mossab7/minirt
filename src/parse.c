#include <minirt.h>

int	parse_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 3 || ft_strcmp(filename + len - 3, ".rt") != 0)
		return (-1);
	return (0);
}

void init_obj_parse_func(t_parse_function *parse_func, t_object_name *obj_name)
{
	obj_name[0] = "A";
	obj_name[1] = "C";
	obj_name[2] = "L";
	obj_name[3] = "sp";
	obj_name[4] = "pl";
	obj_name[5] = "cy";
	
	parse_func[0] = parse_amb_light;
	parse_func[1] = parse_camera;
	parse_func[2] = parse_light;
	parse_func[3] = parse_sphare;
	parse_func[4] = parse_plane;
	parse_func[5] = parse_cylinder;

}

void	parse_obj_data(char **data, t_scene *scene)
{
	t_parse_function	parse_func[OBJ_COUNT];
	char				*obj_name[OBJ_COUNT];
	int					i;

	init_obj_parse_func(parse_func, obj_name);
	while (i < OBJ_COUNT)
	{
		if (ft_strcmp(data[0], obj_name[i]) == 0)
		{
			parse_func[i](data, scene);
			break ;
		}
		i++;
	}
	if (i == OBJ_COUNT)
	{
		ft_putstr_fd("Error: Unknown object type\n", 2);
		return ;
	}
}

void  parse_amb_light(char **data, t_scene *scene)
{
	scene->amb_light.ratio = ft_atof(data[1]);
	scene->amb_light.color = ft_atoi_base(data[2], 16);
}

void  parse_camera(char **data, t_scene *scene)
{
	scene->camera.position = ft_atoi_base(data[1], 16);
	scene->camera.direction = ft_atoi_base(data[2], 16);
	scene->camera.fov = ft_atof(data[3]);
}
void  parse_light(char **data, t_scene *scene)
{
	scene->light.position = ft_atoi_base(data[1], 16);
	scene->light.color = ft_atoi_base(data[2], 16);
	scene->light.intensity = ft_atof(data[3]);
}
void  parse_sphare(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = SPHERE;
	obj->obj.sphere.center = ft_atoi_base(data[1], 16);
	obj->obj.sphere.diameter = ft_atof(data[2]);
	obj->obj.sphere.color = ft_atoi_base(data[3], 16);
	container_push_back(scene->objects, obj);
}
void  parse_plane(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = PLANE;
	obj->obj.plane.center = ft_atoi_base(data[1], 16);
	obj->obj.plane.normal = ft_atoi_base(data[2], 16);
	obj->obj.plane.color = ft_atoi_base(data[3], 16);
	container_push_back(scene->objects, obj);
}
void  parse_cylinder(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->obj.cylinder.center = ft_atoi_base(data[1], 16);
	obj->obj.cylinder.axis = ft_atoi_base(data[2], 16);
	obj->obj.cylinder.diameter = ft_atof(data[3]);
	obj->obj.cylinder.height = ft_atof(data[4]);
	obj->obj.cylinder.color = ft_atoi_base(data[5], 16);
	container_push_back(scene->objects, obj);
}
void  parse_hyperboloid(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = HYPERBOLDOID;
	obj->obj.hyperboloid.center = ft_atoi_base(data[1], 16);
	obj->obj.hyperboloid.axis = ft_atoi_base(data[2], 16);
	obj->obj.hyperboloid.diameter = ft_atof(data[3]);
	obj->obj.hyperboloid.height = ft_atof(data[4]);
	obj->obj.hyperboloid.color = ft_atoi_base(data[5], 16);
	container_push_back(scene->objects, obj);
}
void  parse_paraboloid(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = PARABOLOID;
	obj->obj.paraboloid.center = ft_atoi_base(data[1], 16);
	obj->obj.paraboloid.axis = ft_atoi_base(data[2], 16);
	obj->obj.paraboloid.diameter = ft_atof(data[3]);
	obj->obj.paraboloid.height = ft_atof(data[4]);
	obj->obj.paraboloid.color = ft_atoi_base(data[5], 16);
	container_push_back(scene->objects, obj);
}

void	read_to_scene(int fd,t_scene *scene)
{
	char	*line;
	char	**data;
	
	while(true)
	{
		line = get_next_line(fd);
		if(line == NULL)
			break;
		data = ft_split(line," ");
		parse_obj_data(data, scene);
		ft_free_2d(data);
	}
}

t_scene *parse_scene(char *filename)
{
	t_scene	*scene;
	int		fd;

	if (parse_filename(filename) == -1)
	{
		ft_putstr_fd("Error: Invalid file name\n", 2);
		return (NULL);
	}
	scene = (t_scene *)alloc(sizeof(t_scene));
	fd = ft_open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_free(scene);
		return (NULL);
	}
	read_to_scene(fd, scene);
	ft_close(fd);
	return (scene);
}
