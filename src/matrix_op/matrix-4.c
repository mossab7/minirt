/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix-4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:33:32 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 23:35:56 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_matrix4d	matrix4d_rotation(t_vec3 rotation)
{
	t_matrix4d	matrix;

	matrix = matrix4d_rotation_x(rotation.x);
	matrix = matrix4d_mult(matrix, matrix4d_rotation_y(rotation.y));
	matrix = matrix4d_mult(matrix, matrix4d_rotation_z(rotation.z));
	return (matrix);
}

t_matrix4d	matrix4d_scale(t_vec3 scale)
{
	t_matrix4d	matrix;

	matrix.data[0][0] = scale.x;
	matrix.data[0][1] = 0.0f;
	matrix.data[0][2] = 0.0f;
	matrix.data[0][3] = 0.0f;
	matrix.data[1][0] = 0.0f;
	matrix.data[1][1] = scale.y;
	matrix.data[1][2] = 0.0f;
	matrix.data[1][3] = 0.0f;
	matrix.data[2][0] = 0.0f;
	matrix.data[2][1] = 0.0f;
	matrix.data[2][2] = scale.z;
	matrix.data[2][3] = 0.0f;
	matrix.data[3][0] = 0.0f;
	matrix.data[3][1] = 0.0f;
	matrix.data[3][2] = 0.0f;
	matrix.data[3][3] = 1.0f;
	return (matrix);
}

t_matrix4d	matrix4d_identity(void)
{
	t_matrix4d	matrix;

	matrix.data[0][0] = 1.0f;
	matrix.data[0][1] = 0.0f;
	matrix.data[0][2] = 0.0f;
	matrix.data[0][3] = 0.0f;
	matrix.data[1][0] = 0.0f;
	matrix.data[1][1] = 1.0f;
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

t_matrix4d	matrix4d_transpose(t_matrix4d matrix)
{
	t_matrix4d	result;

	int (i), (j);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.data[i][j] = matrix.data[j][i];
			j++;
		}
		i++;
	}
	return (result);
}
