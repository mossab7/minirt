/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:09:00 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 16:09:02 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt.h"

t_texture	*load_texture(char *filename);
t_color		get_pixel_color(t_texture *texture, int x, int y);
void		free_texture(void *texture_void);

#endif
