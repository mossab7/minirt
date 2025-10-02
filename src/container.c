/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:14:21 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 17:52:42 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>

void	container_push_back(t_container *container, void *item)
{
	if (container->size == container->capacity)
	{
		container->capacity *= CONTAINER_GROWTH_FACTOR;
		container->data = ft_realloc(container->data,
				container->size * sizeof(void *),
				container->capacity * sizeof(void *));
		if (!container->data)
		{
			perror("Failed to allocate memory");
			safe_exit(EXIT_FAILURE);
		}
	}
	((void **)container->data)[container->size++] = item;
}

t_container	*container_init(void)
{
	t_container (*container) = alloc(sizeof(t_container));
	container->data = alloc(CONTAINER_INIT_CAPACITY * sizeof(void *));
	container->size = 0;
	container->capacity = CONTAINER_INIT_CAPACITY;
	return (container);
}
