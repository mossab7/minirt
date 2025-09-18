/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations-1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:19:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/17 17:23:03 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_program	**get_program(void)
{
	static t_program	*program;

	if (!program)
	{
		program = alloc(sizeof(t_program));
		program->scene = NULL;
		program->mlx = NULL;
	}
	return (&program);
}

void	free_all_textures(t_scene *scene)
{
	size_t		i;
	t_object	*obj;
	t_object	**array;

	if (!scene)
		return ;
	array = (t_object **)scene->objects->data;
	i = 0;
	while (i < scene->objects->size)
	{
		obj = array[i];
		free_texture(obj->pattern.texture);
		i++;
	}
}

t_object	*get_object(t_container *container, size_t index)
{
	t_object	*obj;

	if (index >= container->size)
		return (NULL);
	obj = ((t_object **)container->data)[index];
	return (obj);
}

t_light	*get_light(t_container *container, size_t index)
{
	t_light	*light;

	if (index >= container->size)
		return (NULL);
	light = ((t_light **)container->data)[index];
	return (light);
}

void	register_allocation(void *ptr, void (*free_func)(void *))
{
	register_memory_allocation(get_memory_tracker(), create_memory_record(ptr,
			free_func));
}
