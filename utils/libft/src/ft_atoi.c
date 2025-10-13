/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/20 17:37:25 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static const char	*skip_spaces(const char *nptr)
{
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	return (nptr);
}

static const char	*resolve_sign(const char *nptr, int *sign)
{
	*sign = 1;
	if (*nptr && (*nptr == '-' || *nptr == '+'))
	{
		if (*nptr == '-')
			*sign = -(*sign);
		nptr++;
	}
	return (nptr);
}

int	ft_atoi(const char *nptr)
{
	long	n;
	long	prev;
	int		sign;

	n = 0;
	nptr = skip_spaces(nptr);
	nptr = resolve_sign(nptr, &sign);
	while (*nptr && ft_isdigit(*nptr))
	{
		prev = n;
		n = (*(nptr++) - '0') + n * 10;
		if (n < prev)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return (n * sign);
}
