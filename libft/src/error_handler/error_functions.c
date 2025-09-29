/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:46:28 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/26 17:56:34 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error_handler.h>

t_error_system *get_error_system()
{
    static t_error_system err = {0, ""};
    return (&err);
}

void set_error(int code, const char *fmt, ...)
{
    t_error_system *err;

	err = get_error_system();
    err->code = code;
    va_list args;
    va_start(args, fmt);
    vsnprintf(err->message, ERR_BUF_SIZE, fmt, args);
    va_end(args);
}

void append_error_detail(const char *fmt, ...)
{
    t_error_system	*err;
	size_t			len;

	err = get_error_system();
    len = ft_strlen(err->message);
    if (len >= ERR_BUF_SIZE - 1)
        return;
    va_list args;
    va_start(args, fmt);
    vsnprintf(err->message + len, ERR_BUF_SIZE - len, fmt, args);
    va_end(args);
}

void	print_error()
{
    t_error_system *err;

	err = get_error_system();
    ft_dprintf(STDERR, COLOR_RED"Error [%d]"COLOR_RESET
		" : %s\n", err->code, err->message);
}
