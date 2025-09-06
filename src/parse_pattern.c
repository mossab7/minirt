/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:30 by deepseeko         #+#    #+#             */
/*   Updated: 2025/07/12 19:02:31 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_pattern(char **data, t_pattern *pattern)
{
	if (!data[0])
	{
		pattern->type = PATTERN_NONE;
		return (0);
	}
	if (ft_strcmp(data[0], "checkerboard") == 0)
	{
		pattern->type = PATTERN_CHECKERBOARD;
		if (!data[1] || !data[2] || !data[3])
		{
			ft_putstr_fd("Error: Missing checkerboard parameters\n", 2);
			safe_exit(1);
		}
		pattern->color1 = get_color(data[1]);
		pattern->color2 = get_color(data[2]);
		pattern->scale = atof(data[3]);
		if (pattern->scale <= 0)
			pattern->scale = CHECKER_SCALE;
		pattern->bump_strength = 0.0;
		return (1);
	}
	else if (ft_strcmp(data[0], "bump") == 0)
	{
		pattern->type = PATTERN_BUMP_MAP;
		if (!data[1] || !data[2])
		{
			ft_putstr_fd("Error: Missing bump map parameters\n", 2);
			safe_exit(1);
		}
		pattern->scale = atof(data[1]);
		pattern->bump_strength = atof(data[2]);
		if (pattern->scale <= 0)
			pattern->scale = BUMP_SCALE;
		if (pattern->bump_strength <= 0)
			pattern->bump_strength = BUMP_STRENGTH;
		pattern->color1 = (t_color){1.0, 1.0, 1.0};
		pattern->color2 = (t_color){0.0, 0.0, 0.0};
		return (1);
	}
	pattern->type = PATTERN_NONE;
	return (0);
}
