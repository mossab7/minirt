/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/19 11:31:24 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_UTILS_H

# define FT_DPRINTF_UTILS_H
# include "libft.h"
# include <stdarg.h>
# define FLAGS "#0-+ "
# define CONVERSIONS "cspdiuxX%"

typedef struct s_flags
{
	int	alt_form;
	int	zero_padded;
	int	left_adjusted;
	int	space_flag;
	int	force_sign;
	int	precision_value;
	int	precision_flag;
	int	width;
	int	coversion;
	int	printed;
	int	total;
	int	fd;
}		t_flags;

int		handle_char(t_flags *f, int c);
int		handle_str(char *str, t_flags *f);
int		handle_ptr(unsigned long long addr, t_flags *f);
int		handle_nbr(int n, t_flags *f);
int		handle_hex(unsigned int x, t_flags *f, char c);
int		handle_unsigned(unsigned int u, t_flags *f);
int		check_valid(const char *fmt);
int		print_width(t_flags *f, int n);
int		get_num_len(unsigned long long n, unsigned int base);
int		print(int fd, char c);
int		catch_err(int n);
int		parse_integer(const char *fmt, int *n, t_flags *f);
void	parse_flags(const char *fmt, t_flags *f);
void	print_conversion(char c, va_list args, t_flags *f);
void	parse_fmt(int fd, const char *fmt, va_list args, t_flags *f);
#endif // !FT_PRINTF_UTILS_H
