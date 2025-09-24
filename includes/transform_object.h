/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:54:53 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 15:54:55 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_OBJECT_H
# define TRANSFORM_OBJECT_H

# include "minirt.h"

void	translate_object(t_object *obj, t_vec3 translation);
void	rotate_object(t_object *obj, t_vec3 rotation_angles);
void	translate_object(t_object *obj, t_vec3 translation);
void	rotate_object(t_object *obj, t_vec3 rotation_angles);
void	recalculate_camera_vectors(t_camera *camera);
void	transforme_camera(t_program *program, t_vec3 rotation, t_vec3 trans);

#endif
