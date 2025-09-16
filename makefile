GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
BOLD		= \033[1m
CLEAR		= \033[K\r
NAME		= minirt
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
LFLAGS		= -lm -lmlx_Linux -lXext -lX11 -lm -lbsd
AR			= ar rcs
INCLUDES	= -I./includes/ -I./libft/ -I./minilibx-linux/
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux
LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
MLX42		= $(addprefix $(MLX_DIR)/, libmlx_Linux.a)
SRC			= src/minirt.c \
			  src/vec_op.c \
			  src/matrix_op.c \
			  src/render.c \
			  src/pattern.c \
			  src/parse_pattern.c \
			  src/transform_object.c \
			  src/parsing/parsing-1.c\
			  src/parsing/parsing-2.c\
			  src/parsing/parsing-3.c\
			  src/parsing/parsing-4.c\
			  src/camera.c \
			  src/texture.c

OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)
	@printf "$(GREEN)$(BOLD)$(NAME) done!$(RESET)\n"

$(NAME): $(MLX42) $(LIBFT) $(OBJ)
	@printf "$(CLEAR)$(YELLOW)linking $(NAME)...$(RESET)\n"
	@$(CC) $(OBJ) $(LFLAGS) $(LIBFT) $(MLX42) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@printf "[$(GREEN)$(BOLD) OK $(RESET)$(BOLD)]$(RESET) compiling $(BOLD)$@...$(RESET)$(CLEAR)\n"
	@$(CC) -c $(CFLAGS) $< $(INCLUDES) -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)/ all
	
$(MLX42):
	@make -C $(MLX_DIR)/ all

clean:
	@make -C $(LIBFT_DIR)/ clean
	@make -C $(MLX_DIR)/ clean
	@rm -rf obj

fclean: clean
	@make -C $(LIBFT_DIR)/ fclean
	@make -C $(MLX_DIR)/ clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
