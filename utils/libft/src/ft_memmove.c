/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	if (dest == src || n == 0)
		return (dest);
	dp = (unsigned char *)dest;
	sp = (const unsigned char *)src;
	if (dp > sp)
	{
		while (n--)
			dp[n] = sp[n];
	}
	else
	{
		ft_memcpy(dp, sp, n);
	}
	return (dest);
}
