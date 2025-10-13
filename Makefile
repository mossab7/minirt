# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/24 00:06:20 by zbengued          #+#    #+#              #
#    Updated: 2025/10/13 13:58:26 by mbouhia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
BOLD		= \033[1m
CLEAR		= \033[K\r
NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror #-g3 -fsanitize=address -fsanitize=leak
LFLAGS		= -lm -lmlx_Linux -lXext -lX11 -lm -lbsd #-g3 -fsanitize=address -fsanitize=leak
AR			= ar rcs
INCLUDES	= -I./includes/ -I./libft/headers/ -I./minilibx-linux/
LIBFT_DIR	= utils/libft
MLX_DIR		= utils/minilibx-linux
LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
MLX42		= $(addprefix $(MLX_DIR)/, libmlx_Linux.a)
SRC			= src/minirt.c \
			  src/parsing/extract_fucntions.c \
			  src/parsing/extract_pattern.c \
			  src/parsing/is_valid_functions.c \
			  src/parsing/parse_ambiant.c \
			  src/parsing/parse_camera.c \
			  src/parsing/parse_cone.c \
			  src/parsing/parse_cylinder.c \
			  src/parsing/parse_light.c \
			  src/parsing/parse_plane.c \
			  src/parsing/parse_scene.c \
			  src/parsing/parse_scene_utils.c \
			  src/parsing/parse_sphere.c \
			  src/parsing/parsing_utils.c \
			  src/container.c \
			  src/render.c \
			  src/free_object.c \
			  src/keys.c \
			  src/keys-2.c \
			  src/transform_object.c \
			  src/matrix_op/matrix-1.c \
			  src/matrix_op/matrix-2.c \
			  src/matrix_op/matrix-3.c \
			  src/matrix_op/matrix-4.c \
			  src/texturing/texturing-1.c \
			  src/texturing/texturing-2.c \
			  src/texturing/texturing-3.c \
			  src/texturing/texturing-4.c \
			  src/texturing/texturing-5.c \
			  src/texturing/texture_cleanup.c \
			  src/calculation/equations-1.c \
			  src/calculation/equations-2.c \
			  src/calculation/equations-3.c \
			  src/calculation/equations-4.c \
			  src/calculation/equations-5.c \
			  src/calculation/equations-6.c \
			  src/calculation/equations-7.c \
			  src/calculation/equations-8.c \
			  src/calculation/equations-9.c \
			  src/calculation/equations-10.c \
			  src/calculation/equations-11.c \
			  src/calculation/equations-12.c \
			  src/vec_op/vec-1.c \
			  src/vec_op/vec-2.c \
			  src/vec_op/vec-3.c
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)
	@printf "$(GREEN)$(BOLD)$(NAME) done!                           $(RESET)\n"

$(NAME): $(MLX42) $(LIBFT) $(OBJ)
	@printf "$(CLEAR)$(YELLOW)linking $(NAME)...$(RESET)\n"
	@$(CC) $(OBJ) $(LFLAGS) $(LIBFT) $(MLX42) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@printf "\r[$(GREEN)$(BOLD) OK $(RESET)$(BOLD)]$(RESET) compiling $(BOLD)$@...$(RESET)$(CLEAR)"
	@$(CC) -c $(CFLAGS) $< $(INCLUDES) -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)/ all
	
$(MLX42):
	@printf "$(YELLOW)Making MLX...\n$(RESET)"
	@printf "Building MLX"; \
	( $(MAKE) --no-print-directory -C $(MLX_DIR) 2> /dev/null > /dev/null) & pid=$$!; \
	while kill -0 $$pid 2>/dev/null; do \
		for dots in "" "." ".." "..."; do \
			printf "\r$(YELLOW)Building MLX%s " "$$dots"; \
			sleep 0.3; \
		done; \
	done; \
	wait $$pid; \
	printf "$(GREEN)\rMLX done!      \n$(RESET)"

clean:
	@make -C $(LIBFT_DIR)/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR)/ fclean
	@make -C $(MLX_DIR)/ clean 2> /dev/null > /dev/null
	@rm -rf obj
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ)
