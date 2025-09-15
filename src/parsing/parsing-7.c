/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@google.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:00:00 by gemini            #+#    #+#             */
/*   Updated: 2025/09/15 00:06:53 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "texture.h"

static int	count_args(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		i++;
	return (i);
}

static void	checkerboard(t_pattern *pattern, char **data, int *i, int totalargs)
{
	pattern->type |= PATTERN_CHECKERBOARD;
	if (*i + 3 >= totalargs)
	{
		ft_putstr_fd("Error: Missing checkerboard params\n", 2);
		return ;
	}
	pattern->color1 = get_color(data[*i + 1]);
	pattern->color2 = get_color(data[*i + 2]);
	pattern->scale = atof(data[*i + 3]);
	*i += 4;
}

static void	bump(t_pattern *pattern, char **data, int *i, int totalargs)
{
	pattern->type |= PATTERN_BUMP_MAP;
	if (*i + 2 >= totalargs)
	{
		ft_putstr_fd("Error: Missing bump map params\n", 2);
		return ;
	}
	pattern->scale = atof(data[*i + 1]);
	pattern->bump_strength = atof(data[*i + 2]);
	*i += 3;
}

static void	texture(t_pattern *pattern, char **data, int *i, int totalargs)
{
	pattern->type |= PATTERN_TEXTURE;
	if (*i + 1 >= totalargs)
	{
		ft_putstr_fd("Error: Missing texture filename\n", 2);
		return ;
	}
	pattern->texture = load_texture(data[*i + 1]);
	*i += 2;
}

int	parse_pattern(char **data, t_pattern *pattern)
{
	int	i;
	int	total_args;

	i = 0;
	total_args = count_args(data);
	pattern->type = PATTERN_NONE;
	while (i < total_args)
	{
		if (ft_strcmp(data[i], "checkerboard") == 0)
			checkerboard(pattern, data, &i, total_args);
		else if (ft_strcmp(data[i], "bump") == 0)
			bump(pattern, data, &i, total_args);
		else if (ft_strcmp(data[i], "texture") == 0)
			texture(pattern, data, &i, total_args);
		else
			return (ft_putstr_fd("Error: Unknown pattern type\n", 2), 1);
	}
	return (0);
}
