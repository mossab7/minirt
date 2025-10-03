/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@google.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 00:00:00 by gemini            #+#    #+#             */
/*   Updated: 2025/09/17 04:32:49 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "texture.h"

void	free_texture(void *texture_void);

void	free_object(void *obj_void)
{
	t_object	*obj;

	if (!obj_void)
		return ;
	obj = (t_object *)obj_void;
	free(obj);
}
