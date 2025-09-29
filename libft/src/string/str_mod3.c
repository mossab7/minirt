/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_mod3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:23:18 by zbengued          #+#    #+#             */
/*   Updated: 2025/09/28 21:41:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

static void	write_char(t_str *str, size_t *write, char c)
{
	str->data[*write] = c;
	(*write)++;
}

static size_t	clean_loop(t_str *str)
{
	size_t	read;
	size_t	write;
	char	last_space;

	read = 0;
	write = 0;
	last_space = 0;
	while (read < str->size)
	{
		if (ft_isspace(str->data[read]))
		{
			if (last_space != str->data[read])
			{
				write_char(str, &write, str->data[read]);
				last_space = str->data[read];
			}
		}
		else
		{
			write_char(str, &write, str->data[read]);
			last_space = 0;
		}
		read++;
	}
	return (write);
}

void	str_reduce_spaces(t_str *str)
{
	size_t	write;

	write = clean_loop(str);
	str->data[write] = '\0';
	str->size = write;
}
