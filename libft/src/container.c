#include <libft.h>

void container_push_back(t_container *container, void *item)
{
    if (container->size == container->capacity)
    {
        container->capacity *= CONTAINER_GROWTH_FACTOR;
        container->data = ft_realloc(container->data, container->capacity * sizeof(void *),container->size * sizeof(void *));
        if (!container->data)
        {
            perror("Failed to allocate memory");
            safe_exit(EXIT_FAILURE);
        }
    }
    ((void **)container->data)[container->size++] = item;
}

t_container *container_init()
{
    t_container *container = alloc(sizeof(t_container));
    container->data = alloc(CONTAINER_INIT_CAPACITY * sizeof(void *));
    container->size = 0;
    container->capacity = CONTAINER_INIT_CAPACITY;
    return container;
}
