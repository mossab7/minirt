/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec-2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 23:16:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/16 23:16:27 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	div_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return (result);
}

t_vec3	mul_scalar_vec3(t_vec3 a, double scalar)
{
	t_vec3	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

t_vec3	div_scalar_vec3(t_vec3 a, double scalar)
{
	t_vec3	result;

	result.x = a.x / scalar;
	result.y = a.y / scalar;
	result.z = a.z / scalar;
	return (result);
}

double	length_vec3(t_vec3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	normalize_vec3(t_vec3 a)
{
	t_vec3	result;
	double	length;

	length = length_vec3(a);
	if (length == 0)
		return (a);
	result.x = a.x / length;
	result.y = a.y / length;
	result.z = a.z / length;
	return (result);
}
