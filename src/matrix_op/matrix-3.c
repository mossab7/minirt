/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix-3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:32:45 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 22:32:50 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	calculate_determinant3x3(t_matrix4d matrix)
{
	return (matrix.data[0][0] * (matrix.data[1][1] * matrix.data[2][2]
			- matrix.data[1][2] * matrix.data[2][1]) - matrix.data[0][1]
		* (matrix.data[1][0] * matrix.data[2][2] - matrix.data[1][2]
			* matrix.data[2][0]) + matrix.data[0][2] * (matrix.data[1][0]
			* matrix.data[2][1] - matrix.data[1][1] * matrix.data[2][0]));
}

t_matrix4d	inverse_rotation_scale(t_matrix4d matrix, double det)
{
	t_matrix4d	result;

	result.data[0][0] = (matrix.data[1][1] * matrix.data[2][2]
			- matrix.data[1][2] * matrix.data[2][1]) / det;
	result.data[0][1] = -(matrix.data[0][1] * matrix.data[2][2]
			- matrix.data[0][2] * matrix.data[2][1]) / det;
	result.data[0][2] = (matrix.data[0][1] * matrix.data[1][2]
			- matrix.data[0][2] * matrix.data[1][1]) / det;
	result.data[1][0] = -(matrix.data[1][0] * matrix.data[2][2]
			- matrix.data[1][2] * matrix.data[2][0]) / det;
	result.data[1][1] = (matrix.data[0][0] * matrix.data[2][2]
			- matrix.data[0][2] * matrix.data[2][0]) / det;
	result.data[1][2] = -(matrix.data[0][0] * matrix.data[1][2]
			- matrix.data[0][2] * matrix.data[1][0]) / det;
	result.data[2][0] = (matrix.data[1][0] * matrix.data[2][1]
			- matrix.data[1][1] * matrix.data[2][0]) / det;
	result.data[2][1] = -(matrix.data[0][0] * matrix.data[2][1]
			- matrix.data[0][1] * matrix.data[2][0]) / det;
	result.data[2][2] = (matrix.data[0][0] * matrix.data[1][1]
			- matrix.data[0][1] * matrix.data[1][0]) / det;
	return (result);
}

void	inverse_translation(t_matrix4d *result, t_matrix4d original_matrix)
{
	result->data[0][3] = -(result->data[0][0] * original_matrix.data[0][3]
			+ result->data[0][1] * original_matrix.data[1][3]
			+ result->data[0][2] * original_matrix.data[2][3]);
	result->data[1][3] = -(result->data[1][0] * original_matrix.data[0][3]
			+ result->data[1][1] * original_matrix.data[1][3]
			+ result->data[1][2] * original_matrix.data[2][3]);
	result->data[2][3] = -(result->data[2][0] * original_matrix.data[0][3]
			+ result->data[2][1] * original_matrix.data[1][3]
			+ result->data[2][2] * original_matrix.data[2][3]);
}

t_matrix4d	matrix4d_inverse(t_matrix4d matrix)
{
	t_matrix4d	result;
	double		det;

	det = calculate_determinant3x3(matrix);
	if (det == 0.0f)
		return (matrix);
	result = inverse_rotation_scale(matrix, det);
	inverse_translation(&result, matrix);
	result.data[3][0] = 0.0f;
	result.data[3][1] = 0.0f;
	result.data[3][2] = 0.0f;
	result.data[3][3] = 1.0f;
	return (result);
}
