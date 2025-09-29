/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:19:54 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/28 23:29:01 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "libft.h"
#include <minirt.h>

#define COLOR_ERROR "Unexpected color format [%s]"

static bool	valid_diameter(double diameter)
{
	return (diameter > 0);
}

static bool	valid_color(t_color *color)
{
	return (color->r >= 0 && color->r <= 255
		&& color->g >= 0 && color->g <= 255
		&& color->b >= 0 && color->b <= 255);
}

static bool	valid_normalvec(t_vec3 vec3)
{
	return (vec3.x >= -1 && vec3.x <= 1
		&& vec3.y >= -1 && vec3.y <= 1
		&& vec3.z >= -1 && vec3.z <= 1);
}

static bool	valid_fov(double fov)
{
	return (fov >= 0 && fov <= 180);
}

static bool	valid_ratio(double ratio)
{
	return (ratio >= 0 && ratio <= 1);
}

t_str	extract_identifier(t_str *line)
{
	size_t	start;
	size_t	end;

	start = 0;
	while (start < line->size && ft_isspace(line->data[start]))
		start++;
	end = start;
	while (end < line->size && !ft_isspace(line->data[end]))
		end++;
	return (str_substr(line, start, end - start));
}

double	extract_fov(t_str *fov_field)
{
	double	fov;

	fov = ft_atof(fov_field->data);
	if (!ft_strisnum(fov_field->data) || !valid_fov(fov))
		return (set_error(1, "Unexpected fov format"), -1);
	return (fov);
}

double	extract_diameter(t_str *diameter_field)
{
	double	diameter;

	diameter = ft_atof(diameter_field->data);
	if (!ft_strisnum(diameter_field->data) || !valid_diameter(diameter))
		return (set_error(1, "Unexpected diameter format [%s]",
				diameter_field->data), -1);
	return (diameter);
}

double	extract_ratio(t_str *ratio_field)
{
	double	ratio;

	ratio = ft_atof(ratio_field->data);
	if (!ft_strisnum(ratio_field->data) || !valid_ratio(ratio))
		return (set_error(1, "Unexpected ratio format [%s]",
				ratio_field->data), -1);
	return (ratio);
}

static void	fill_color(t_color *color, t_str *rgb)
{
	color->r = ft_atoi(rgb[0].data);
	color->g = ft_atoi(rgb[1].data);
	color->b = ft_atoi(rgb[2].data);
}

t_color	extract_color(t_str *color_field)
{
	t_color	*color;
	t_str	*rgb;
	size_t	count;

	double (r), g, b;
	color = malloc(sizeof(t_color));
	if (!color)
		return (set_error(ERR_MALLOC, "malloc failed"), (t_color){0,0,0});
	rgb = str_split(color_field, ',', &count);
	if (!rgb || count != 3)
		return (str_free_array(rgb, count),
			set_error(1, COLOR_ERROR, color_field->data), (t_color){0,0,0});
	count = -1;
	while (++count < 3)
	{
		if (!ft_strisnum(rgb[count].data))
			return (str_free_array(rgb, 3),
				set_error(1, COLOR_ERROR, color_field->data), (t_color){0,0,0});
	}
	fill_color(color, rgb);
	if (!valid_color(color))
		return (str_free_array(rgb, 3),
			set_error(1, COLOR_ERROR, color_field->data), (t_color){0,0,0});
	return (r = color->r / COLOR_MAX, g = color->g / COLOR_MAX,
			b = color->b / COLOR_MAX, free(color), (t_color){r, g, b});
}

t_vec3	extract_vec3(t_str *vec3_field)
{
	t_vec3	vec3;
	t_str	*coords;
	size_t	count;

	str_peek_reset(vec3_field);
	coords = str_split(vec3_field, ',', &count);
	if (!coords || count != 3)
		return (str_free_array(coords, count),
			set_error(1, "Unexpected coordonate format [%s]",
				vec3_field->data), (t_vec3){0, 0, 0});
	count = -1;
	while (++count < 3)
	{
		if (!ft_strisnum(coords[count].data))
			return (str_free_array(coords, 3),
				set_error(1, "Unexpected coordonate format [%s]",
					vec3_field->data), (t_vec3){0, 0, 0});
	}
	vec3.x = ft_atof(coords[0].data);
	vec3.y = ft_atof(coords[1].data);
	vec3.z = ft_atof(coords[2].data);
	return (vec3);
}

t_vec3	extract_normalvec(t_str *vec3_field)
{
	t_vec3	vec3;

	vec3 = extract_vec3(vec3_field);
	if (get_error_system()->code)
		return (append_error_detail(" in normalized vector"), (t_vec3){0, 0, 0});
	if (!valid_normalvec(vec3))
		return (set_error(1, "Unexpected normalized vector format [%s]",
				vec3_field->data), (t_vec3){0, 0, 0});
	return (vec3);
}

static void	checkerboard(t_pattern *pattern, t_str *data, size_t *i, size_t totalargs)
{
	pattern->type |= PATTERN_CHECKERBOARD;
	if (*i + 3 >= totalargs)
	{
		ft_putstr_fd("Error: Missing checkerboard params\n", 2);
		return ;
	}
	pattern->color1 = extract_color(&data[*i + 1]);
	pattern->color2 = extract_color(&data[*i + 2]);
	pattern->scale = ft_atof(data[*i + 3].data);
	*i += 4;
}

static void	bump(t_pattern *pattern, t_str *data, size_t *i, size_t totalargs)
{
	pattern->type |= PATTERN_BUMP_MAP;
	if (*i + 2 >= totalargs)
	{
		ft_putstr_fd("Error: Missing bump map params\n", 2);
		return ;
	}
	pattern->scale = ft_atof(data[*i + 1].data);
	pattern->bump_strength = ft_atof(data[*i + 2].data);
	*i += 3;
}

static void	texture(t_pattern *pattern, t_str *data, size_t *i, size_t totalargs)
{
	pattern->type |= PATTERN_TEXTURE;
	if (*i + 1 >= totalargs)
	{
		ft_putstr_fd("Error: Missing texture filename\n", 2);
		return ;
	}
	pattern->texture = load_texture(data[*i + 1].data);
	*i += 2;
}

t_pattern_entry	*patt_entry(void)
{
	static t_pattern_entry	arr[] = {
		{"chekerboard", 11, checkerboard},
		{"bump", 4, bump},
		{"texture", 7, texture},
		{NULL, 0, NULL}
	};

	return (arr);
}

void	extract_pattern(t_str *fields, t_pattern *pattern, size_t count, size_t start)
{
	size_t	i;
	
	i = start;
	pattern->type = PATTERN_NONE;
	while (i < count)
	{
		if (ft_strcmp(fields[i].data, "checkerboard") == 0)
			checkerboard(pattern, fields, &i, count);
		else if (ft_strcmp(fields[i].data, "bump") == 0)
			bump(pattern, fields, &i, count);
		else if (ft_strcmp(fields[i].data, "texture") == 0)
			texture(pattern, fields, &i, count);
		else if (fields[i].data[0] == '\0')
			i++;
		else
		{
			set_error(7, "Error: Unknown pattern type [%s]", fields[i].data);
			return ;
		}
	}
}
