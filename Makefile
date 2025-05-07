NAME = Cube

SRC = src/main.c 

OBJ = ${SRC:.c=.o}

MLXLIB = ./minilibx-linux/libmlx_Linux.a

all: $(MLXLIB) $(NAME) 

$(MLXLIB):
	make -C minilibx-linux/
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXLIB) -Lmlx_linux  -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) #-g -fsanitize=address

%.o: %.c includes/cub3d.h
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(OBJ)
	make clean -C minilibx-linux/

fclean: clean
	rm -rf $(NAME)

re: fclean all