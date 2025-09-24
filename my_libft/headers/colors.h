/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:19:28 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/20 15:40:41 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
#define COLORS_H

// Reset
# define COLOR_RESET       "\001\033[0m\002"

// Styles
# define STYLE_BOLD        "\001\033[1m\002"
# define STYLE_DIM         "\001\033[2m\002"
# define STYLE_UNDERLINE   "\001\033[4m\002"
# define STYLE_BLINK       "\001\033[5m\002"
# define STYLE_REVERSE     "\001\033[7m\002"
# define STYLE_HIDDEN      "\001\033[8m\002"

// Colors text (standard)
# define COLOR_BLACK       "\001\033[0;30m\002"
# define COLOR_RED         "\001\033[0;31m\002"
# define COLOR_GREEN       "\001\033[0;32m\002"
# define COLOR_YELLOW      "\001\033[0;33m\002"
# define COLOR_BLUE        "\001\033[0;34m\002"
# define COLOR_MAGENTA     "\001\033[0;35m\002"
# define COLOR_CYAN        "\001\033[0;36m\002"
# define COLOR_WHITE       "\001\033[0;37m\002"

// Colors text (bright)
# define COLOR_BRIGHT_BLACK    "\001\033[1;30m\002"
# define COLOR_BRIGHT_RED      "\001\033[1;31m\002"
# define COLOR_BRIGHT_GREEN    "\001\033[1;32m\002"
# define COLOR_BRIGHT_YELLOW   "\001\033[1;33m\002"
# define COLOR_BRIGHT_BLUE     "\001\033[1;34m\002"
# define COLOR_BRIGHT_MAGENTA  "\001\033[1;35m\002"
# define COLOR_BRIGHT_CYAN     "\001\033[1;36m\002"
# define COLOR_BRIGHT_WHITE    "\001\033[1;37m\002"

// Backgroud Colors (background)
# define BG_BLACK          "\001\033[40m\002"
# define BG_RED            "\001\033[41m\002"
# define BG_GREEN          "\001\033[42m\002"
# define BG_YELLOW         "\001\033[43m\002"
# define BG_BLUE           "\001\033[44m\002"
# define BG_MAGENTA        "\001\033[45m\002"
# define BG_CYAN           "\001\033[46m\002"
# define BG_WHITE          "\001\033[47m\002"

// Backgroud Colors (bright)
# define BG_BRIGHT_BLACK   "\001\033[100m\002"
# define BG_BRIGHT_RED     "\001\033[101m\002"
# define BG_BRIGHT_GREEN   "\001\033[102m\002"
# define BG_BRIGHT_YELLOW  "\001\033[103m\002"
# define BG_BRIGHT_BLUE    "\001\033[104m\002"
# define BG_BRIGHT_MAGENTA "\001\033[105m\002"
# define BG_BRIGHT_CYAN    "\001\033[106m\002"
# define BG_BRIGHT_WHITE   "\001\033[107m\002"

#endif /* COLORS_H */
