#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdlib.h>

#define CONTAINER_GROWTH_FACTOR 2
#define CONTAINER_INIT_CAPACITY 4

typedef struct s_container
{
    void    *data;
    size_t  size;
    size_t  capacity; 
} t_container;


#endif // CONTAINER_H