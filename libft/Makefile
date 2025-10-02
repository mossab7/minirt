BOLD		= \033[1m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m
CLEAR		= \033[K\r
NAME		= libft.a
INCLUDES	= -I./headers/
CC			= cc -c -Wall -Wextra -Werror -g3 #-fsanitize=address -fsanitize=leak
AR			= ar rcs
SRC			= src/ft_isalnum.c \
			  src/ft_isalpha.c \
			  src/ft_isascii.c \
			  src/ft_isdigit.c \
			  src/ft_isprint.c \
			  src/ft_isblank.c \
			  src/ft_isspace.c \
			  src/ft_itoa.c \
			  src/ft_atof.c \
			  src/ft_atoi.c \
			  src/ft_atol.c \
			  src/ft_bzero.c \
			  src/ft_calloc.c \
			  src/ft_malloc.c \
			  src/ft_realloc.c \
			  src/ft_memchr.c \
			  src/ft_memcmp.c \
			  src/ft_memcpy.c \
			  src/ft_strisnum.c \
			  src/ft_strndup.c \
			  src/ft_memmove.c \
			  src/ft_memset.c \
			  src/ft_putchar_fd.c \
			  src/ft_putendl_fd.c \
			  src/ft_putnbr_fd.c \
			  src/ft_putstr_fd.c \
			  src/ft_split.c \
			  src/ft_strisempty.c \
			  src/ft_strisdecimal.c \
			  src/ft_strchr.c \
			  src/ft_strdup.c \
			  src/ft_striteri.c \
			  src/ft_strjoin.c \
			  src/ft_strlcat.c \
			  src/ft_strlcpy.c \
			  src/ft_strlen.c \
			  src/ft_strlen_until.c \
			  src/ft_strmapi.c \
			  src/ft_strncmp.c \
			  src/ft_strnstr.c \
			  src/ft_strrchr.c \
			  src/ft_strtrim.c \
			  src/ft_substr.c \
			  src/ft_tolower.c \
			  src/ft_strcmp.c \
			  src/ft_toupper.c \
			  src/linked_list/ft_lstprint.c \
			  src/linked_list/ft_lstassign_index.c \
			  src/linked_list/ft_lstadd_back.c \
			  src/linked_list/ft_lstadd_front.c \
			  src/linked_list/ft_lstclear.c \
			  src/linked_list/ft_lstpush.c \
			  src/linked_list/ft_lstswap.c \
			  src/linked_list/ft_lstrotate.c \
			  src/linked_list/ft_lstreverse_rotate.c \
			  src/linked_list/ft_lstdelone.c \
			  src/linked_list/ft_lstiter.c \
			  src/linked_list/ft_lstlast.c \
			  src/linked_list/ft_lstmap.c \
			  src/linked_list/ft_lstnew.c \
			  src/linked_list/ft_lstsize.c \
			  src/ft_tokenize.c \
			  src/ft_execvpe.c \
			  src/ft_getenv.c \
			  src/ft_getpath.c \
			  src/ft_free_vector.c \
			  src/ft_free.c \
			  src/ft_printf/ft_printf.c \
			  src/ft_printf/parsing.c \
			  src/ft_printf/print_char.c \
			  src/ft_printf/print_hex.c \
			  src/ft_printf/print_nbr.c \
			  src/ft_printf/print_ptr.c \
			  src/ft_printf/print_str.c \
			  src/ft_printf/print_unsigned.c \
			  src/ft_printf/utils.c \
			  src/ft_dprintf/ft_dprintf.c \
			  src/ft_dprintf/d_parsing.c \
			  src/ft_dprintf/d_print_char.c \
			  src/ft_dprintf/d_print_hex.c \
			  src/ft_dprintf/d_print_nbr.c \
			  src/ft_dprintf/d_print_ptr.c \
			  src/ft_dprintf/d_print_str.c \
			  src/ft_dprintf/d_print_unsigned.c \
			  src/ft_dprintf/d_utils.c \
			  src/get_next_line/get_next_line.c \
			  src/get_next_line/get_next_line_bonus.c \
			  src/get_next_line/get_next_line_utils.c \
			  src/get_next_line/get_next_line_utils_bonus.c \
			  src/string/read_file.c \
			  src/string/str_arr_core.c \
			  src/string/str_arr_extra.c \
			  src/string/str_arr_utils.c \
			  src/string/str_build.c \
			  src/string/str_convert.c \
			  src/string/str_core.c \
			  src/string/str_mod1.c \
			  src/string/str_mod2.c \
			  src/string/str_mod3.c \
			  src/string/str_peek.c \
			  src/string/str_seg1.c \
			  src/string/str_seg2.c \
			  src/string/str_shift.c \
			  src/string/str_utils.c \
			  src/error_handler/error_functions.c \
			  src/ternary.c \
			  src/resource_man.c \
			  src/resource_man_utils.c \
			  src/ft_getoutput.c
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
RM			= rm -rf

all: $(NAME)


$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@printf "$(GREEN)$(BOLD)Libft.a done!                           $(RESET)\n"

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
