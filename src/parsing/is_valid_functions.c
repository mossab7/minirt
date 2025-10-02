/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:39:44 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:39:49 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	valid_diameter(double diameter)
{
	return (diameter > 0);
}

bool	valid_color(t_color *color)
{
	return (color->r >= 0 && color->r <= 255
		&& color->g >= 0 && color->g <= 255
		&& color->b >= 0 && color->b <= 255);
}

bool	valid_normalvec(t_vec3 vec3)
{
	return (vec3.x >= -1 && vec3.x <= 1
		&& vec3.y >= -1 && vec3.y <= 1
		&& vec3.z >= -1 && vec3.z <= 1);
}

bool	valid_fov(double fov)
{
	return (fov >= 0 && fov <= 180);
}

bool	valid_ratio(double ratio)
{
	return (ratio >= 0 && ratio <= 1);
}
