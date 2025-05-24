CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = src/minirt.c src/parse.c src/vec_op.c src/matrix_op.c src/render.c

all : LIBFT
	$(CC) $(CFLAGS) $(SRC)  -Iincludes -Llibft -o minirt minilibx-linux/libmlx_Linux.a -lft -lXext -lX11 -lm -lbsd

LIBFT:
	make -C libft

clean : 
	make -C libft clean

fclean : 
	make -C libft fclean

re : fclean all




