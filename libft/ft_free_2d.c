/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:04:05 by lazmoud           #+#    #+#             */
/*   Updated: 2025/04/14 22:05:00 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>

static size_t	ft_2d_size(char **v)
{
	size_t	i;

	i = 0;
	while (v[i])
		i++;
	return (i);
}

char	**ft_free_2d(char **v, size_t size)
{
	size_t	e;

	if (v)
	{
		if (size == 0)
			size = ft_2d_size(v);
		e = 0;
		while (e < size)
		{
			ft_free(v[e]);
			e++;
		}
		ft_free(v);
	}
	return (NULL);
}
