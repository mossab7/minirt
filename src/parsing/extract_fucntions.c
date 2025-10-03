/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_fucntions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:40:57 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 18:02:27 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

#define COLOR_ERROR "Unexpected color format [%s]"

double	extract_ratio(t_str *ratio_field)
{
	double	ratio;

	ratio = ft_atof(ratio_field->data);
	if (!ft_strisnum(ratio_field->data) || !valid_ratio(ratio))
		return (set_error(1, "Unexpected ratio format [%s]",
				ratio_field->data), -1);
	return (ratio);
}

void	fill_color(t_color *color, t_str *rgb)
{
	color->r = ft_atoi(rgb[0].data);
	color->g = ft_atoi(rgb[1].data);
	color->b = ft_atoi(rgb[2].data);
}

t_color	extract_color(t_str *color_field)
{
	t_str	*rgb;
	size_t	count;

	double (r), g, b;
	t_color (color);
	rgb = str_split(color_field, ',', &count);
	if (!rgb || count != 3)
		return (str_free_array(rgb, count),
			set_error(1, COLOR_ERROR, color_field->data), (t_color){0, 0, 0});
	count = -1;
	while (++count < 3)
	{
		if (!ft_strisnum(rgb[count].data))
			return (str_free_array(rgb, 3),
				set_error(1, COLOR_ERROR, color_field->data),
				(t_color){0, 0, 0});
	}
	fill_color(&color, rgb);
	if (!valid_color(&color))
		return (str_free_array(rgb, 3),
			set_error(1, COLOR_ERROR, color_field->data), (t_color){0, 0, 0});
	return (str_free_array(rgb, count), r = color.r / 255, g = color.g / 255,
		b = color.b / 255, (t_color){r, g, b});
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
	return (str_free_array(coords, 3), vec3);
}

t_vec3	extract_normalvec(t_str *vec3_field)
{
	t_vec3	vec3;

	vec3 = extract_vec3(vec3_field);
	if (get_error_system()->code)
		return (append_error_detail(" in normalized vector"),
			(t_vec3){0, 0, 0});
	if (!valid_normalvec(vec3))
		return (set_error(1, "Unexpected normalized vector format [%s]",
				vec3_field->data), (t_vec3){0, 0, 0});
	return (vec3);
}
