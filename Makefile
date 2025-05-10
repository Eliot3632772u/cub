NAME = Cube

SRC = src/main.c src/animation.c src/dda_init_values.c src/dda.c src/doors.c src/draw_frame_utils.c src/draw_frame.c src/init.c src/key_hooks.c src/minimap.c src/movements.c src/ray_casting.c src/rotation.c src/wall_height.c 

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