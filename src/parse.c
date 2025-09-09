#include <minirt.h>
#include "../includes/camera.h"

int	parse_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 3 || ft_strcmp(filename + len - 3, ".rt") != 0)
		return (-1);
	return (0);
}

void init_obj_parse_func(t_parse_function *parse_func, char **obj_name)
{
	obj_name[OBJ_AMB_LIGHT] = "A";
	obj_name[OBJ_CAMERA] = "C";
	obj_name[OBJ_LIGHT] = "L";
	obj_name[OBJ_SPHERE] = "sp";
	obj_name[OBJ_PLANE] = "pl";
	obj_name[OBJ_CYLINDER] = "cy";

	parse_func[OBJ_AMB_LIGHT] = parse_amb_light;
	parse_func[OBJ_CAMERA] = parse_camera;
	parse_func[OBJ_LIGHT] = parse_light;
	parse_func[OBJ_SPHERE] = parse_sphare;
	parse_func[OBJ_PLANE] = parse_plane;
	parse_func[OBJ_CYLINDER] = parse_cylinder;
}

void	parse_obj_data(char **data, t_scene *scene)
{
	t_parse_function	parse_func[OBJ_COUNT];
	char				*obj_name[OBJ_COUNT];
	int					i;

	// Skip empty lines and comments
	if (!data[0] || data[0][0] == '\n' || data[0][0] == '#' || ft_strlen(data[0]) == 0)
		return ;

	init_obj_parse_func(parse_func, obj_name);
	i = 0;
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
		printf("Error: Unknown object type |'%s'|\n", data[0]);
		return ;
	}
}

t_color get_color(char *data)
{
    t_color color;
    char **rgb;

    rgb = ft_split(data, ',');
    if (!rgb || !rgb[RED_INDEX] || !rgb[GREEN_INDEX] || !rgb[BLUE_INDEX]) {
        ft_putstr_fd("Error: Invalid color format\n", 2);
        safe_exit(1);
    }
    color.r = atof(rgb[RED_INDEX]);
    color.g = atof(rgb[GREEN_INDEX]);
    color.b = atof(rgb[BLUE_INDEX]);
    ft_free_2d(rgb, -1);
    if (color.r < COLOR_MIN || color.r > COLOR_MAX
        || color.g < COLOR_MIN || color.g > COLOR_MAX
        || color.b < COLOR_MIN || color.b > COLOR_MAX)
    {
        ft_putstr_fd("Error: Invalid color value\n", 2);
        safe_exit(1);
    }
	color.r /= COLOR_MAX;
	color.g /= COLOR_MAX;
	color.b /= COLOR_MAX;
    return (color);
}

t_vec3 get_vec3(char *vec)
{
	t_vec3	vec3;
	char 	**v;

	v = ft_split(vec, ',');
	if (!v || !v[X_INDEX] || !v[Y_INDEX] || !v[Z_INDEX])
	{
		ft_putstr_fd("Error: Invalid vector format\n", 2);
		safe_exit(1);
	}
	vec3.x = atof(v[X_INDEX]);
	vec3.y = atof(v[Y_INDEX]);
	vec3.z = atof(v[Z_INDEX]);
	ft_free_2d(v,-1);
	return (vec3);
}

void parse_amb_light(char **data, t_scene *scene)
{
    scene->amb_light.ratio = atof(data[1]);
    if (scene->amb_light.ratio < LIGHT_RATIO_MIN || scene->amb_light.ratio > LIGHT_RATIO_MAX)
    {
        ft_putstr_fd("Error: Invalid ambient light ratio\n", 2);
        safe_exit(1);
    }
    scene->amb_light.color = get_color(data[2]);
}

void	check_vec_range(t_vec3 vec)
{
	if (vec.x < VEC_MIN || vec.x > VEC_MAX
		|| vec.y < VEC_MIN || vec.y > VEC_MAX
		|| vec.z < VEC_MIN || vec.z > VEC_MAX)
	{
		fprintf(stderr, "Error: Invalid vector range %f,%f,%f\n", vec.x, vec.y, vec.z);
		safe_exit(1);
	}
}

double dgree_to_rad(double degree)
{
	return (degree * M_PI) / 180.0;
}

void parse_camera(char **data, t_scene *scene)
{
    scene->camera.position = get_vec3(data[1]);
    scene->camera.direction = get_vec3(data[2]);
    check_vec_range(scene->camera.direction);
    scene->camera.fov = atof(data[3]);
    if (scene->camera.fov < FOV_MIN || scene->camera.fov > FOV_MAX)
    {
        ft_putstr_fd("Error: Invalid camera FOV\n", 2);
        safe_exit(1);
    }
	scene->camera.direction = add_vec3(scene->camera.direction, VEC_EPSILON);
	scene->camera.direction = normalize_vec3(scene->camera.direction);
	scene->camera.width = tan(dgree_to_rad(scene->camera.fov / 2));
	scene->camera.height = scene->camera.width / RATIO;
    recalculate_camera_vectors(&scene->camera);
}

void parse_light(char **data, t_scene *scene)
{
    scene->light.position = get_vec3(data[1]);
    scene->light.intensity = atof(data[2]);
    if (scene->light.intensity > 1.0f || scene->light.intensity < 0.0f)
    {
        ft_putstr_fd("Error: Invalid light intensity\n", 2);
        safe_exit(1);
    }
    scene->light.color = get_color(data[3]);
}

void parse_sphare(char **data, t_scene *scene)
{
    t_sphere sphere;

    sphere.center = get_vec3(data[1]);
    sphere.diameter = atof(data[2]);
    if (sphere.diameter <= 0)
    {
        ft_putstr_fd("Error: Invalid sphere diameter\n", 2);
        safe_exit(1);
    }
    sphere.color = get_color(data[3]);

    if (data[4])
        parse_pattern(&data[4], &sphere.pattern);
    else
        sphere.pattern.type = PATTERN_NONE;

    t_object *obj = alloc(sizeof(t_object));
    obj->type = SPHERE;
    obj->obj.sphere = sphere;
    container_push_back(scene->objects, obj);
}

void  parse_plane(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = PLANE;
	obj->obj.plane.center = get_vec3(data[1]);
	obj->obj.plane.normal = get_vec3(data[2]);
	check_vec_range(obj->obj.plane.normal);
	obj->obj.plane.color = get_color(data[3]);

	if (data[4])
		parse_pattern(&data[4], &obj->obj.plane.pattern);
	else
		obj->obj.plane.pattern.type = PATTERN_NONE;

	container_push_back(scene->objects, obj);
}
void  parse_cylinder(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = CYLINDER;
	obj->obj.cylinder.center = get_vec3(data[1]);
	obj->obj.cylinder.axis = get_vec3(data[2]);
	check_vec_range(obj->obj.cylinder.axis);
	obj->obj.cylinder.diameter = atof(data[3]);
	obj->obj.cylinder.height = atof(data[4]);
	obj->obj.cylinder.color = get_color(data[5]);

	if (data[6])
		parse_pattern(&data[6], &obj->obj.cylinder.pattern);
	else
		obj->obj.cylinder.pattern.type = PATTERN_NONE;

	container_push_back(scene->objects, obj);
}
void  parse_hyperboloid(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = HYPERBOLDOID;
	obj->obj.hyperboloid.center = get_vec3(data[1]);
	obj->obj.hyperboloid.axis = get_vec3(data[2]);
	check_vec_range(obj->obj.hyperboloid.axis);
	obj->obj.hyperboloid.diameter = atof(data[3]);
	obj->obj.hyperboloid.height = atof(data[4]);
	obj->obj.hyperboloid.color = get_color(data[5]);
	container_push_back(scene->objects, obj);
}
void  parse_paraboloid(char **data, t_scene *scene)
{
	t_object	*obj;

	obj = (t_object *)alloc(sizeof(t_object));
	obj->type = PARABOLOID;
	obj->obj.paraboloid.center = get_vec3(data[1]);
	obj->obj.paraboloid.axis = get_vec3(data[2]);
	check_vec_range(obj->obj.paraboloid.axis);
	obj->obj.paraboloid.diameter = atof(data[3]);
	obj->obj.paraboloid.height = atof(data[4]);
	obj->obj.paraboloid.color = get_color(data[5]);
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
		if (line[0] == '#' || line[0] == '\n' || ft_strlen(line) <= 1)
		{
			ft_free(line);
			continue;
		}
		data = ft_split(line, ' ');
		if (data && data[0])
			parse_obj_data(data, scene);
		ft_free_2d(data,-1);
		ft_free(line);
	}
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)alloc(sizeof(t_scene));
	scene->objects = container_init();
	return (scene);
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
	scene = init_scene();
	fd = ft_open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_free(scene);
		return (NULL);
	}
	read_to_scene(fd, scene);
	ft_close((void *)(intptr_t)fd);
	return (scene);
}
