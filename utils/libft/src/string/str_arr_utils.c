/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

t_str	*str_arr_peek(t_str_arr *arr)
{
	if (arr->peek >= arr->size)
		return (NULL);
	return (&arr->items[arr->peek]);
}

t_str	*str_arr_peek_advance(t_str_arr *arr)
{
	if (arr->peek >= arr->size)
		return (NULL);
	return (&arr->items[arr->peek++]);
}

void	str_arr_peek_reset(t_str_arr *arr)
{
	arr->peek = 0;
}

void	str_arr_insert(t_str_arr *arr, size_t index, char *text)
{
	t_str	new_str;
	size_t	i;

	if (index > arr->size)
		return ;
	if (!str_arr_resize_if_needed(arr))
		return ;
	i = arr->size;
	while (i > index)
	{
		arr->items[i] = arr->items[i - 1];
		i--;
	}
	str_create(&new_str, text);
	arr->items[index] = new_str;
	arr->size++;
}

void	str_arr_remove(t_str_arr *arr, size_t index)
{
	size_t	i;

	if (index >= arr->size)
		return ;
	str_destroy(&arr->items[index]);
	i = index;
	while (i + 1 < arr->size)
	{
		arr->items[i] = arr->items[i + 1];
		i++;
	}
	arr->size--;
}
