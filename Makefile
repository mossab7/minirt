NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

# Source files
SRCS = $(SRC_DIR)/minirt.c \
       $(SRC_DIR)/parse.c \
       $(SRC_DIR)/vec_op.c \
       $(SRC_DIR)/matrix_op.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/pattern.c \
       $(SRC_DIR)/parse_pattern.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx_Linux.a

# Include flags
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Linking flags
LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lmlx_Linux -lXext -lX11 -lm -lbsd

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
