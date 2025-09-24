/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_seg2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/26 18:37:40 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	str_segment_set(t_str *str, size_t start, size_t length, size_t end)
{
	char	*ptr;

	if (!str)
		return ;
	ptr = ft_calloc(length + 1, sizeof(char));
	ft_memset(ptr, str_peek(str), length);
	str_segment_remove(str, start, end - start);
	str_insert(str, start, ptr);
}

size_t	str_segments_count(t_str *str, char delimiter)
{
	size_t	count;
	size_t	i;

	if (!str || !str->size)
		return (0);
	count = 1;
	i = 0;
	while (i < str->size)
	{
		if (str->data[i] == delimiter)
			count++;
		i++;
	}
	return (count);
}

int	str_match(t_str *str, char *target, int (*cmp)(const char *, const char *,
			size_t), size_t start)
{
	size_t	len;

	if (!str || !target || !cmp || start >= str->size)
		return (0);
	len = ft_strlen(target);
	if (start + len > str->size)
		return (0);
	return (!cmp(str->data + start, target, len));
}
