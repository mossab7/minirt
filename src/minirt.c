#include <minirt.h>

t_program **get_program(void)
{
    static t_program *program;

    if (!program)
    {
        program = alloc(sizeof(t_program));
        program->scene = NULL;
        program->mlx = NULL;
    }

    return (&program);
}

void destroy_window(void *ptr)
{
    (void)ptr;
    t_program *program;

    program = *get_program();
    mlx_destroy_window(program->mlx->mlx_ptr, program->mlx->win_ptr);
}

void destroy_image(void *ptr)
{
    (void)ptr;
    t_program *program;

    program = *get_program();
    mlx_destroy_image(program->mlx->mlx_ptr, program->mlx->canvas->img_ptr);
}

t_object *get_object(t_container *container, size_t index)
{
    t_object *obj;

    if (index >= container->size)
        return (NULL);
    obj = ((t_object **)container->data)[index];
    return (obj);
}

void register_allocation(void *ptr, void (*free_func)(void *))
{
    register_memory_allocation(get_memory_tracker(),
    create_memory_record(ptr, free_func));
}

t_canvas *init_canvas(void *mlx_ptr, int width, int height)
{
    t_canvas *canvas;

    canvas = alloc(sizeof(t_canvas));
    canvas->img_ptr = mlx_new_image(mlx_ptr, width, height);
    if (!canvas->img_ptr)
    {
        ft_putstr_fd("Error: Failed to create image\n", 2);
        safe_exit(1);
    }
    canvas->addr = mlx_get_data_addr(canvas->img_ptr,
            &canvas->bpp, &canvas->line_length, &canvas->endian);
    return (canvas);
}

t_mlx *_init_mlx(void)
{
    t_mlx *mlx;

    mlx = alloc(sizeof(t_mlx));
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
    {
        ft_putstr_fd("Error: Failed to initiate mlx connection\n", 2);
        safe_exit(1);
    }
    register_allocation(mlx->mlx_ptr, free);
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
    if (!mlx->win_ptr)
    {
        ft_putstr_fd("Error: Failed to create window\n", 2);
        safe_exit(1);
    }
    mlx->canvas = init_canvas(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    return (mlx);
}

int main(int argc, char **argv)
{
    t_program *program;
    
    if (argc != 2)
    {
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return (1);
    }
    
    program = *get_program();
    program->scene = parse_scene(argv[1]);
    program->mlx = _init_mlx();  
    
    render_scene(program);
    mlx_loop(program->mlx->mlx_ptr);
    
    safe_exit(0);
}