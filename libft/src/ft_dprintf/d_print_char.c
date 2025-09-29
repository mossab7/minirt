/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_print_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_utils.h"

int	handle_char(t_flags *f, int c)
{
	int	count;

	count = 0;
	if (!f->left_adjusted)
		count += print_width(f, 1);
	count += print(f->fd, c);
	if (f->left_adjusted)
		count += print_width(f, 1);
	return (count);
}
