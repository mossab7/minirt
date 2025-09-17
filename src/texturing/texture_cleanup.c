/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@google.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 23:00:00 by gemini            #+#    #+#             */
/*   Updated: 2025/09/17 03:21:27 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "texture.h"

void	free_texture(void *texture_void)
{
	t_texture	*texture;

	if (!texture_void)
		return ;
	texture = (t_texture *)texture_void;
	if (texture->img_ptr && texture->mlx_ptr)
	{
		mlx_destroy_image(texture->mlx_ptr, texture->img_ptr);
		texture->img_ptr = NULL;
	}
	free(texture);
}
