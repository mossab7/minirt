CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC =

all :
	$(CC) $(CFLAGS) $(SRC) -lmlx -lXext -lX11 -lm -lz






