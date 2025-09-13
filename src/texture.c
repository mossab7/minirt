#include "texture.h"

t_texture *load_texture(char *filename)
{
    t_program *program;
    t_texture *texture;

    program = *get_program();
    texture = alloc(sizeof(t_texture));
    texture->img_ptr = mlx_xpm_file_to_image(program->mlx->mlx_ptr, filename, &texture->width, &texture->height);
    if (!texture->img_ptr)
    {
        ft_putstr_fd("Error: Failed to load texture file: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd("\n", 2);
        safe_exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp, &texture->line_length, &texture->endian);
    return (texture);
}

t_color get_pixel_color(t_texture *texture, int x, int y)
{
    char    *dst;
    int     color_val;
    t_color color;

    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return ((t_color){1, 0, 1}); // Return magenta for out-of-bounds as a debug indicator
    dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
    color_val = *(unsigned int*)dst;
    color.r = ((color_val >> 16) & 0xFF) / 255.0;
    color.g = ((color_val >> 8) & 0xFF) / 255.0;
    color.b = (color_val & 0xFF) / 255.0;
    return (color);
}

