/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix-2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:26:32 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 23:49:19 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	matrix4d_mult_vec3(t_matrix4d matrix, t_vec3 vec)
{
	t_vec3	result;

	result.x = matrix.data[0][0] * vec.x + matrix.data[0][1] * vec.y
		+ matrix.data[0][2] * vec.z + matrix.data[0][3];
	result.y = matrix.data[1][0] * vec.x + matrix.data[1][1] * vec.y
		+ matrix.data[1][2] * vec.z + matrix.data[1][3];
	result.z = matrix.data[2][0] * vec.x + matrix.data[2][1] * vec.y
		+ matrix.data[2][2] * vec.z + matrix.data[2][3];
	return (result);
}

t_matrix4d	matrix4d_scaling(t_vec3 scale)
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

t_matrix4d	view_matrix(t_vec3 camera_pos, t_vec3 camera_dir)
{
	t_matrix4d	translation;
	t_matrix4d	rotation;
	t_matrix4d	view;
	t_vec3		neg_pos;

	neg_pos = vec3_negate(camera_pos);
	translation = matrix4d_translation(neg_pos);
	rotation = matrix4d_rotation(camera_dir);
	rotation = matrix4d_transpose(rotation);
	view = matrix4d_mult(rotation, translation);
	return (view);
}
