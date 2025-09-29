/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strisnum(const char *str)
{
	int	i;
	int	digit;

	i = 0;
	digit = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i] && ft_isdigit(str[i]))
	{
		digit = 1;
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		digit = 1;
		i++;
	}
	if (i == 0 || str[i] || digit == 0)
		return (0);
	return (1);
}
