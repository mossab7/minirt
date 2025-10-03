/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	write_num(char *buf, int n)
{
	long	num;
	size_t	i;

	i = 0;
	if (!n)
	{
		buf[i++] = '0';
	}
	if (n < 0)
	{
		num = -(long)n;
	}
	else
		num = (long)n;
	while (num > 0)
	{
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		buf[i++] = '-';
	buf[i] = '\0';
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	size_t	bytes;
	int		count;

	bytes = write_num(str, n);
	count = 0;
	while (bytes--)
		count += ft_putchar_fd(str[bytes], fd);
	return (count);
}
