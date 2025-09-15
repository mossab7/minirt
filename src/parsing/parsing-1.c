/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:55:01 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 23:55:01 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	parse_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 3 || ft_strcmp(filename + len - 3, ".rt") != 0)
		return (-1);
	return (0);
}

void	init_obj_parse_func(t_parse_function *parse_func, char **obj_name)
{
	obj_name[OBJ_AMB_LIGHT] = "A";
	obj_name[OBJ_CAMERA] = "C";
	obj_name[OBJ_LIGHT] = "L";
	obj_name[OBJ_SPHERE] = "sp";
	obj_name[OBJ_PLANE] = "pl";
	obj_name[OBJ_CYLINDER] = "cy";
	obj_name[OBJ_CONE] = "co";
	parse_func[OBJ_AMB_LIGHT] = parse_amb_light;
	parse_func[OBJ_CAMERA] = parse_camera;
	parse_func[OBJ_LIGHT] = parse_light;
	parse_func[OBJ_SPHERE] = parse_sphare;
	parse_func[OBJ_PLANE] = parse_plane;
	parse_func[OBJ_CYLINDER] = parse_cylinder;
	parse_func[OBJ_CONE] = parse_cone;
}

void	parse_obj_data(char **data, t_scene *scene)
{
	t_parse_function	parse_func[OBJ_COUNT];
	char				*obj_name[OBJ_COUNT];
	int					i;

	if (!data[0] || data[0][0] == '\n' || data[0][0] == '#'
		|| ft_strlen(data[0]) == 0)
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

t_color	get_color(char *data)
{
	t_color	color;
	char	**rgb;

	rgb = ft_split(data, ',');
	if (!rgb || !rgb[RED_INDEX] || !rgb[GREEN_INDEX] || !rgb[BLUE_INDEX])
	{
		ft_putstr_fd("Error: Invalid color format\n", 2);
		safe_exit(1);
	}
	color.r = atof(rgb[RED_INDEX]);
	color.g = atof(rgb[GREEN_INDEX]);
	color.b = atof(rgb[BLUE_INDEX]);
	ft_free_2d(rgb, -1);
	if (color.r < COLOR_MIN || color.r > COLOR_MAX || color.g < COLOR_MIN
		|| color.g > COLOR_MAX || color.b < COLOR_MIN || color.b > COLOR_MAX)
	{
		ft_putstr_fd("Error: Invalid color value\n", 2);
		safe_exit(1);
	}
	color.r /= COLOR_MAX;
	color.g /= COLOR_MAX;
	color.b /= COLOR_MAX;
	return (color);
}

t_vec3	get_vec3(char *vec)
{
	t_vec3	vec3;
	char	**v;

	v = ft_split(vec, ',');
	if (!v || !v[X_INDEX] || !v[Y_INDEX] || !v[Z_INDEX])
	{
		ft_putstr_fd("Error: Invalid vector format\n", 2);
		safe_exit(1);
	}
	vec3.x = atof(v[X_INDEX]);
	vec3.y = atof(v[Y_INDEX]);
	vec3.z = atof(v[Z_INDEX]);
	ft_free_2d(v, -1);
	return (vec3);
}
