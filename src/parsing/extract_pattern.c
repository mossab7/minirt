/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:38:06 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 18:01:47 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	checkerboard(t_pattern *pattern, t_str *data,
		size_t *i, size_t totalargs)
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

static void	texture(t_pattern *pattern,
		t_str *data, size_t *i, size_t totalargs)
{
	pattern->type |= PATTERN_TEXTURE;
	if (*i + 1 >= totalargs)
	{
		ft_putstr_fd("Error: Missing texture filename\n", 2);
		return ;
	}
	pattern->texture = load_texture(data[*i + 1].data);
	if (get_error_system()->code)
		return ;
	*i += 2;
}

void	extract_pattern(t_str *fields,
		t_pattern *pattern, size_t count, size_t start)
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
		{
			texture(pattern, fields, &i, count);
			if (get_error_system()->code)
				return ;
		}
		else if (fields[i].data[0] == '\0')
			i++;
		else
			set_error(7, "Error: Unknown pattern type [%s]", fields[i].data);
		if (get_error_system()->code)
			return ;
	}
}
