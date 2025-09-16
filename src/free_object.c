/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@google.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 00:00:00 by gemini            #+#    #+#             */
/*   Updated: 2025/09/17 00:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "texture.h"

// Forward declaration for free_texture, assuming it's not in a common header
void	free_texture(void *texture_void);

void	free_object(void *obj_void)
{
	t_object	*obj;
	t_pattern	*pattern;

	if (!obj_void)
		return ;
	obj = (t_object *)obj_void;
	pattern = NULL;
	if (obj->type == SPHERE)
		pattern = &obj->obj.sphere.pattern;
	else if (obj->type == PLANE)
		pattern = &obj->obj.plane.pattern;
	else if (obj->type == CYLINDER)
		pattern = &obj->obj.cylinder.pattern;
	else if (obj->type == CONE)
		pattern = &obj->obj.cone.pattern;
	if (pattern && (pattern->type & PATTERN_TEXTURE) && pattern->texture)
	{
		free_texture(pattern->texture);
		pattern->texture = NULL;
	}
	free(obj);
}
