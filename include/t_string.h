/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_string.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:15:46 by lazmoud           #+#    #+#             */
/*   Updated: 2025/04/14 22:16:08 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef T_STRING_H
# define T_STRING_H
# include <stdlib.h>

# define VAC_INIT_CAP 16
# define VAC_GROWTH_FACTOR 2

typedef struct s_string
{
	char	*cstring;
	size_t	size;
	size_t	cap;
	int		cursor;
}			t_string;

t_string	*str_construct(void);
int			str_search(t_string *vec, const char *text, int offset);
int			str_search_using_cursor(t_string *vec, const char *text);
t_string	*vstr_construct(size_t count, ...);
void		str_expand(t_string *vec);
void		str_push_back(t_string *vec, uintptr_t item);
void		str_append(char *src, t_string *vec);
void		str_overwrite(char *src, t_string *vec);
void		str_destruct(t_string *vec);
void		str_join(t_string *vec, size_t count, ...);
void		str_expand_anyhow(t_string *vec);
void		str_print(t_string *str);
#endif // !T_STRING_H
