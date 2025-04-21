#include <minirt.h>

t_string_vector *read_to_vstring(char *filename)
{
	t_string_vector *vstring;
	int 			fd;
	char			tmp;

	vstring = strv_construct();
	fd = open(filename, O_RDONLY);
	while(true)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break;
		strv_push_back(vstring, tmp);
		ft_free(tmp);
	}
	return (vstring);
}

void	parse_ambient(t_scene_items *scene_data, char *params)
{
	char	**split_params;

	split_params = ft_split(params, SEPARATORS);
	scene_data->id = ft_strdup("A");
	stack_push_back(scene_data->params->items, atof(split_params[1]));
	if (scene_data->params->items[0] < 0 || scene_data->params->items[0] > 1)
		cleanexit("Error: Ambient light intensity must be between 0 and 1");
}

void	parse_camera(t_scene_items *scene_items, char *params)
{
	char	**split_params;

	split_params = ft_split(params, SEPARATORS);
	scene_items->id = ft_strdup("C");
}

void	get_light(t_scene_items *scene_items, char *params)
{
	stack_push_back(scene_items->params->items, atof(params));
	if (scene_items->params->items[0] < 0 || scene_items->params->items[0] > 1)
		cleanexit("Error: Light intensity must be between 0 and 1");
}

void	get_rgb(t_scene_items *scene_items, char *params)
{
	char	**split_params;
	double	r;
	double	g;
	double	b;

	split_params = ft_split(params, SEPARATORS);
	r = atof(split_params[0]);
	g = atof(split_params[1]);
	b = atof(split_params[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		cleanexit("Error: RGB values must be between 0 and 255");
	scene_items->params->items[0] = r;
	scene_items->params->items[1] = g;
	scene_items->params->items[2] = b;
}

void	parse_light(t_scene_items *scene_items, char *params)
{
	char	**split_params;

	split_params = ft_split(params, SEPARATORS);
	scene_items->id = ft_strdup("L");
	get_light(scene_items, split_params[1]);
}

void	parse_sphere(t_scene_items *scene_items, char *params)
{
	char	**split_params;

	split_params = ft_split(params, SEPARATORS);
	scene_items->id = ft_strdup("sp");
}

void	parse_plane(t_scene_items *scene_items, char *params)
{
	char	**split_params;

	split_params = ft_split(params, SEPARATORS);
	scene_items->id = ft_strdup("pl");
}

void	parse_cylinder(t_scene_items *scene_items, char *params)
{
	char	**split_params;

	split_params = ft_split(params, SEPARATORS);
	scene_items->id = ft_strdup("cy");
}

t_scene_items	*get_param(char **params)
{
	t_scene_items	*scene_data;
	size_t			iter;

	str_push_back(scene_data->id, params[0]);
	iter = 1;
	while (params[iter])
	{
		stack_push_back(scene_data->params, atof(params[iter]));
		iter++;
	}
	return (scene_data);
}

t_scene_items_vector	*load_to_scenedata(t_string_vector *vstring)
{
	t_scene_items_vector *scene_data;
	char				**params;
	size_t				iter;

	iter = 0;
	scene_data = vsd_construct();
	while (iter < vstring->size)
	{
		params = ft_split(vstring->cstrings[iter], SPACE);
		vsd_push_back(scene_data,get_params(params));
		iter++;
	}
	return (scene_data);
}

void	parse_scene(t_program *program, char *filename)
{
	t_string_vector	*vstring;

	vstring = read_to_vstring(filename);
	program->scene_data = load_to_scenedata(vstring);
}
