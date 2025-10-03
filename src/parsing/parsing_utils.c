/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:19:54 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:41:59 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
