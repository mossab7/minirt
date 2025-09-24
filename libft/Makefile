# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 23:41:44 by zbengued          #+#    #+#              #
#    Updated: 2025/09/24 02:28:57 by zbengued         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

BOLD		= \033[1m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m
CLEAR		= \033[K\r
NAME		= libft.a
INCLUDES	= -I./headers/
CC			= cc -c -Wall -Wextra -Werror
AR			= ar rcs
SRC = src/ft_atoi.c \
	  src/ft_atof.c \
	  src/ft_bzero.c \
	  src/ft_isalnum.c \
	  src/ft_isalpha.c \
	  src/ft_isascii.c \
	  src/ft_isdigit.c \
	  src/ft_isprint.c \
	  src/ft_memchr.c \
	  src/ft_memcmp.c \
	  src/ft_memcpy.c \
	  src/ft_memset.c \
	  src/ft_tolower.c \
	  src/ft_toupper.c \
	  src/ft_memmove.c \
	  src/ft_strlen.c \
	  src/ft_strchr.c \
	  src/ft_strdup.c \
	  src/ft_strlcat.c \
	  src/ft_strlcpy.c \
	  src/ft_strrchr.c \
	  src/ft_strncmp.c \
	  src/ft_strnstr.c \
	  src/ft_calloc.c \
	  src/ft_substr.c \
	  src/ft_itoa.c \
	  src/ft_split.c \
	  src/ft_strjoin.c \
	  src/ft_strtrim.c \
	  src/ft_strmapi.c \
	  src/ft_striteri.c \
	  src/ft_putchar_fd.c \
	  src/ft_putstr_fd.c \
	  src/ft_putendl_fd.c \
	  src/ft_putnbr_fd.c \
	  src/resource_man.c \
	  src/ft_lstadd_back_bonus.c \
	  src/ft_lstadd_front_bonus.c \
	  src/ft_lstclear_bonus.c \
	  src/ft_lstdelone_bonus.c \
	  src/ft_lstiter_bonus.c \
	  src/ft_lstlast_bonus.c \
	  src/ft_lstmap_bonus.c \
	  src/ft_lstnew_bonus.c \
	  src/resource_man_utils.c \
	  src/ft_lstsize_bonus.c \
	  src/ft_strcmp.c \
	  src/ft_realloc.c \
	  src/ft_free.c \
	  src/ft_malloc.c \
	  src/ft_ispunct.c \
	  src/ft_isspace.c \
	  src/ft_isquote.c \
	  src/ft_free_vector.c \
	  src/ft_atol_base.c \
	  src/container.c \
	  src/get_next_line.c \
	  src/get_next_line_utils.c \
	  src/ft_is_not_null.c \
	  src/ft_isdir.c \
	  src/ft_split_set.c \
	  src/ft_free_2d.c \
	  src/ternary.c \
	  src/string/read_file.c \
	  src/string/str_arr_core.c \
	  src/string/str_arr_extra.c \
	  src/string/str_arr_utils.c \
	  src/string/str_build.c \
	  src/string/str_convert.c \
	  src/string/str_core.c \
	  src/string/str_mod1.c \
	  src/string/str_mod2.c \
	  src/string/str_peek.c \
	  src/string/str_seg1.c \
	  src/string/str_seg2.c \
	  src/string/str_shift.c \
	  src/string/str_utils.c
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
RM			= rm -rf

all: $(NAME)


$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@printf "\r$(GREEN)$(BOLD)Libft.a done!                                             $(RESET)\n"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $< $(INCLUDES) -o $@
	@printf "\r[$(GREEN)$(BOLD) OK $(RESET)$(BOLD)]$(RESET) inserting $(BOLD)$@...$(RESET)$(CLEAR)"
	@$(AR) $(NAME) $@

clean :
	@printf "$(RED)Cleaning $(OBJ_DIR)...$(RESET)\n"
	@${RM} obj

fclean : clean
	@printf "$(RED)Cleaning $(NAME)...$(RESET)\n"
	@${RM} $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
