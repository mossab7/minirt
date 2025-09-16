/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix-1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:23:35 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 22:23:35 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_matrix4d	matrix4d_translation(t_vec3 translation)
{
	t_matrix4d	matrix;

	matrix.data[0][0] = 1.0f;
	matrix.data[0][1] = 0.0f;
	matrix.data[0][2] = 0.0f;
	matrix.data[0][3] = translation.x;
	matrix.data[1][0] = 0.0f;
	matrix.data[1][1] = 1.0f;
	matrix.data[1][2] = 0.0f;
	matrix.data[1][3] = translation.y;
	matrix.data[2][0] = 0.0f;
	matrix.data[2][1] = 0.0f;
	matrix.data[2][2] = 1.0f;
	matrix.data[2][3] = translation.z;
	matrix.data[3][0] = 0.0f;
	matrix.data[3][1] = 0.0f;
	matrix.data[3][2] = 0.0f;
	matrix.data[3][3] = 1.0f;
	return (matrix);
}

t_matrix4d	matrix4d_rotation_x(double angle)
{
	t_matrix4d	matrix;

	matrix.data[0][0] = 1.0f;
	matrix.data[0][1] = 0.0f;
	matrix.data[0][2] = 0.0f;
	matrix.data[0][3] = 0.0f;
	matrix.data[1][0] = 0.0f;
	matrix.data[1][1] = cos(angle);
	matrix.data[1][2] = -sin(angle);
	matrix.data[1][3] = 0.0f;
	matrix.data[2][0] = 0.0f;
	matrix.data[2][1] = sin(angle);
	matrix.data[2][2] = cos(angle);
	matrix.data[2][3] = 0.0f;
	matrix.data[3][0] = 0.0f;
	matrix.data[3][1] = 0.0f;
	matrix.data[3][2] = 0.0f;
	matrix.data[3][3] = 1.0f;
	return (matrix);
}

t_matrix4d	matrix4d_rotation_y(double angle)
{
	t_matrix4d	matrix;

	matrix.data[0][0] = cos(angle);
	matrix.data[0][1] = 0.0f;
	matrix.data[0][2] = sin(angle);
	matrix.data[0][3] = 0.0f;
	matrix.data[1][0] = 0.0f;
	matrix.data[1][1] = 1.0f;
	matrix.data[1][2] = 0.0f;
	matrix.data[1][3] = 0.0f;
	matrix.data[2][0] = -sin(angle);
	matrix.data[2][1] = 0.0f;
	matrix.data[2][2] = cos(angle);
	matrix.data[2][3] = 0.0f;
	matrix.data[3][0] = 0.0f;
	matrix.data[3][1] = 0.0f;
	matrix.data[3][2] = 0.0f;
	matrix.data[3][3] = 1.0f;
	return (matrix);
}

t_matrix4d	matrix4d_rotation_z(double angle)
{
	t_matrix4d	matrix;

	matrix.data[0][0] = cos(angle);
	matrix.data[0][1] = -sin(angle);
	matrix.data[0][2] = 0.0f;
	matrix.data[0][3] = 0.0f;
	matrix.data[1][0] = sin(angle);
	matrix.data[1][1] = cos(angle);
	matrix.data[1][2] = 0.0f;
	matrix.data[1][3] = 0.0f;
	matrix.data[2][0] = 0.0f;
	matrix.data[2][1] = 0.0f;
	matrix.data[2][2] = 1.0f;
	matrix.data[2][3] = 0.0f;
	matrix.data[3][0] = 0.0f;
	matrix.data[3][1] = 0.0f;
	matrix.data[3][2] = 0.0f;
	matrix.data[3][3] = 1.0f;
	return (matrix);
}

t_matrix4d	matrix4d_mult(t_matrix4d a, t_matrix4d b)
{
	t_matrix4d	result;

	int (i), (j), (k);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			result.data[i][j] = 0.0f;
			while (k < 4)
			{
				result.data[i][j] += a.data[i][k] * b.data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}
