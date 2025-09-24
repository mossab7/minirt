/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:43:59 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/26 17:38:42 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER
# define ERROR_HANDLER

# include <libft.h>
# include <stdarg.h>
# include <stdio.h>

# define ERR_BUF_SIZE 256
# define ERR_MALLOC -3
# define ERR_MALLOC_MESSAGE "malloc failed"

typedef struct s_error_system
{
    int			code;
    char	message[ERR_BUF_SIZE];
}	t_error_system;

t_error_system	*get_error_system();
void			set_error(int code, const char *fmt, ...);
void			append_error_detail(const char *fmt, ...);
void			print_error();
#endif // !ERROR_HANDLER



