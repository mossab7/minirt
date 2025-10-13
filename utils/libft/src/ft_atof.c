/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	ft_atof(char *str)
{
	double	f;
	int		exp;
	int		sign;

	sign = 1;
	exp = 10;
	f = 0;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		f = f * 10 + (*(str++) - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		f = f + (double)(*str++ - '0') / exp;
		exp *= 10;
	}
	return (f * sign);
}
