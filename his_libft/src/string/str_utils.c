/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/26 18:41:48 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	str_total_size(t_str *arr, size_t len, size_t delim_len)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (i < len)
	{
		total += arr[i].size;
		if (i < len - 1)
			total += delim_len;
		i++;
	}
	return (total);
}

void	str_fill(t_str *result, t_str *arr, size_t len, char *d)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str_append(result, arr[i].data);
		if (i < len - 1 && d)
			str_append(result, d);
		i++;
	}
}

void	str_fill_split(t_str *str, char d, t_str *arr, size_t c)
{
	size_t	i;
	size_t	start;
	size_t	part;

	i = 0;
	start = 0;
	part = 0;
	while (i <= str->size && part < c)
	{
		if (i == str->size || str->data[i] == d)
		{
			arr[part++] = str_substr(str, start, i - start);
			i++;
			start = i;
		}
		else
			i++;
	}
}

int	str_arr_resize_if_needed(t_str_arr *arr)
{
	t_str	*tmp;
	size_t	i;

	if (arr->size < arr->capacity)
		return (1);
	tmp = ft_calloc(sizeof(t_str), arr->capacity * 2);
	if (!tmp)
		return (0);
	i = arr->size;
	while (i--)
		tmp[i] = arr->items[i];
	free(arr->items);
	arr->items = tmp;
	arr->capacity *= 2;
	return (1);
}

void	str_free_array(t_str *arr, size_t count)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		str_destroy(&arr[i]);
		i++;
	}
	free(arr);
}
