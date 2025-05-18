CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = src/minirt.c src/parse.c

all : LIBFT
	$(CC) $(CFLAGS) $(SRC)  -lft -Llibft -Iincludes -o minirt

LIBFT:
	make -C libft

clean : 
	make -C libft clean

fclean : 
	make -C libft fclean

re : fclean all




