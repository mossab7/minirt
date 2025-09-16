/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@google.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 23:00:00 by gemini            #+#    #+#             */
/*   Updated: 2025/09/16 23:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "texture.h"

void	free_texture(void *texture_void)
{
	t_texture	*texture;
	t_program	*program;

	if (!texture_void)
		return ;
	texture = (t_texture *)texture_void;
	program = *get_program();
	if (texture->img_ptr && program->mlx && program->mlx->mlx_ptr)
		mlx_destroy_image(program->mlx->mlx_ptr, texture->img_ptr);
	free(texture);
}
