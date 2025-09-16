#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt.h"

t_texture	*load_texture(char *filename);
t_color		get_pixel_color(t_texture *texture, int x, int y);
void		free_texture(void *texture_void);

#endif