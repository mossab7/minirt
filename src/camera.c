/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:19:45 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/14 22:19:51 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"

void	recalculate_camera_vectors(t_camera *camera)
{
	camera->right = normalize_vec3(cross_vec3(camera->direction, UPVEC));
	camera->up = normalize_vec3(cross_vec3(camera->direction, camera->right));
	camera->right = normalize_vec3(cross_vec3(camera->direction, camera->up));
}
