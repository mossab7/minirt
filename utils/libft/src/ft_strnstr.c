/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (ft_strlen(haystack) < nlen || len < nlen)
		return (NULL);
	i = 0;
	if (needle[0])
	{
		while (haystack[i] && i < len)
		{
			if (haystack[i] == needle[0])
			{
				j = 0;
				while (i + j < len && needle[j] && needle[j] == haystack[i + j])
					j++;
				if (needle[j] == '\0')
					return ((char *)(haystack + i));
			}
			i++;
		}
		return (NULL);
	}
	return ((char *)(haystack));
}
