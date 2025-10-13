/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:14:40 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/20 03:14:41 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H

# include <stdlib.h>

# define CONTAINER_GROWTH_FACTOR 2
# define CONTAINER_INIT_CAPACITY 4

typedef struct s_container
{
	void	*data;
	size_t	size;
	size_t	capacity;
}			t_container;

void		container_push_back(t_container *container, void *item);
t_container	*container_init(void);

#endif // CONTAINER_H
