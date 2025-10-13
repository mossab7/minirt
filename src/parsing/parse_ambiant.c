/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:28:33 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 18:01:03 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	parse_ambient(t_scene *scene, t_str *line)
{
	size_t	count;
	t_str	*fields;

	str_reduce_spaces(line);
	fields = str_split(line, ' ', &count);
	if (count < 3)
	{
		set_error(7, "Missing fields");
		str_free_array(fields, count);
		return ;
	}
	scene->amb_light.ratio = extract_ratio(&fields[1]);
	scene->amb_light.color = extract_color(&fields[2]);
	end_of_line_parse(fields, count, 2);
	if (get_error_system()->code)
	{
		str_free_array(fields, count);
		return ;
	}
	str_free_array(fields, count);
}
