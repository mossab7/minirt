/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static int	printnstr(t_flags *f, char *str, int len)
{
	int	count;
	int	n;

	count = 0;
	n = len;
	if (!f->left_adjusted)
		count += print_width(f, len);
	while (n-- && *str)
		count += print(*(str++));
	if (f->left_adjusted)
		count += print_width(f, len);
	return (count);
}

static int	handle_str_precision(t_flags *f, char *str)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(str);
	if (f->precision_flag && f->precision_value < len)
		len = f->precision_value;
	count += printnstr(f, str, len);
	return (count);
}

static int	handle_null_str(t_flags *f)
{
	int		count;
	char	*str;

	count = 0;
	str = "(null)";
	if (f->precision_flag && f->precision_value >= 0
		&& f->precision_value < (int) ft_strlen(str))
		count += print_width(f, 0);
	else
		count += handle_str_precision(f, str);
	return (count);
}

int	handle_str(char *str, t_flags *f)
{
	int	count;

	count = 0;
	if (!str)
		count += handle_null_str(f);
	else
		count += handle_str_precision(f, str);
	return (count);
}
