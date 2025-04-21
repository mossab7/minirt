CC = cc
RM = rm -rf
CFLAGS = Wall Werror Wextra
LIBFT = ft
LIBFT_DIR = ./libft
SRC = /src/minirt.c
INCLUDE = include/libft.h include/t_strng.h include/t_string_vector.h
NAME = minirt

all : $(NAME)

$(LIBFT) : make -c (LIBFT_DIR)

NAME : $(LIBFT) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) -L$(IBFT_DIR) -l$(LIBFT) -I./include

clean :
	make -C $(LIBFT_DIR) clean

fclean : clean
	make -C $(LIBFT) fclean
	$(RM) $(MAME)




