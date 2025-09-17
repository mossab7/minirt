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

	if (!obj_void)
		return ;
	obj = (t_object *)obj_void;
	// Accéder directement au pattern de l'objet
	if ((obj->pattern.type & PATTERN_TEXTURE) && obj->pattern.texture)
	{
		free_texture(obj->pattern.texture);
		obj->pattern.texture = NULL;
	}
	free(obj);
}
