#include <minirt.h>

t_object *get_object(t_container *container, size_t index)
{
    t_object *obj;

    if (index >= container->size)
        return (NULL);
    obj = ((t_object **)container->data)[index];
    return (obj);
}

int main(int argc, char **argv)
{
    t_scene	*scene;

    if (argc != 2)
    {
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return (1);
    }
    scene = parse_scene(argv[1]);
    print_scene(scene);
    (void)scene;
    //render_scene(scene);
    safe_exit(0);
}