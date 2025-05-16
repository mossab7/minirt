#include <minirt.h>

t_object *get_object(t_container *container, int index)
{
    t_object *obj;

    if (index < 0 || index >= container->size)
        return (NULL);
    obj = ((t_object **)container->data)[index];
    return (obj);
}

char *get_type(t_object_type type)
{
    if (type == SPHERE)
        return ("SPHERE");
    else if (type == PLANE)
        return ("PLANE");
    else if (type == CYLINDER)
        return ("CYLINDER");
    else if (type == HYPERBOLDOID)
        return ("HYPERBOLDOID");
    else if (type == PARABOLOID)
        return ("PARABOLOID");
    return ("UNKNOWN");
}

int main(int argc, char **argv)
{
    t_scene	*scene;
    int		fd;

    if (argc != 2)
    {
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return (1);
    }
    scene = parse_scene(argv[1]);
    for (int i = 0; i < scene->objects->size; i++)
    {
       printf("Object %d: %s\n", i, get_type(get_object(scene->objects, i)->type));
    }
    render_scene(scene);
    safe_exit(0);
}