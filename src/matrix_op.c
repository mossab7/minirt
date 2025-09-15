/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:02:49 by deepseeko         #+#    #+#             */
/*   Updated: 2025/09/14 23:35:47 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

//
// t_matrix4d	matrix4d_inverse(t_matrix4d matrix)
// {
// 	t_matrix4d	result;
// 	double		det;
//
// 	det = matrix.data[0][0] * (matrix.data[1][1] * matrix.data[2][2]
// 			- matrix.data[1][2] * matrix.data[2][1]) - matrix.data[0][1]
// 		* (matrix.data[1][0] * matrix.data[2][2] - matrix.data[1][2]
// 			* matrix.data[2][0]) + matrix.data[0][2] * (matrix.data[1][0]
// 			* matrix.data[2][1] - matrix.data[1][1] * matrix.data[2][0]);
// 	if (det == 0.0f)
// 		return (matrix);
// 	result.data[0][0] = (matrix.data[1][1] * matrix.data[2][2]
// 			- matrix.data[1][2] * matrix.data[2][1]) / det;
// 	result.data[0][1] = -(matrix.data[0][1] * matrix.data[2][2]
// 			- matrix.data[0][2] * matrix.data[2][1]) / det;
// 	result.data[0][2] = (matrix.data[0][1] * matrix.data[1][2]
// 			- matrix.data[0][2] * matrix.data[1][1]) / det;
// 	result.data[1][0] = -(matrix.data[1][0] * matrix.data[2][2]
// 			- matrix.data[1][2] * matrix.data[2][0]) / det;
// 	result.data[1][1] = (matrix.data[0][0] * matrix.data[2][2]
// 			- matrix.data[0][2] * matrix.data[2][0]) / det;
// 	result.data[1][2] = -(matrix.data[0][0] * matrix.data[1][2]
// 			- matrix.data[0][2] * matrix.data[1][0]) / det;
// 	result.data[2][0] = (matrix.data[1][0] * matrix.data[2][1]
// 			- matrix.data[1][1] * matrix.data[2][0]) / det;
// 	result.data[2][1] = -(matrix.data[0][0] * matrix.data[2][1]
// 			- matrix.data[0][1] * matrix.data[2][0]) / det;
// 	result.data[2][2] = (matrix.data[0][0] * matrix.data[1][1]
// 			- matrix.data[0][1] * matrix.data[1][0]) / det;
// 	result.data[0][3] = -(result.data[0][0] * matrix.data[0][3]
// 			+ result.data[0][1] * matrix.data[1][3] + result.data[0][2]
// 			* matrix.data[2][3]);
// 	result.data[1][3] = -(result.data[1][0] * matrix.data[0][3]
// 			+ result.data[1][1] * matrix.data[1][3] + result.data[1][2]
// 			* matrix.data[2][3]);
// 	result.data[2][3] = -(result.data[2][0] * matrix.data[0][3]
// 			+ result.data[2][1] * matrix.data[1][3] + result.data[2][2]
// 			* matrix.data[2][3]);
// 	result.data[3][0] = 0.0f;
// 	result.data[3][1] = 0.0f;
// 	result.data[3][2] = 0.0f;
// 	result.data[3][3] = 1.0f;
// 	return (result);
// }
