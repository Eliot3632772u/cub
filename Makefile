NAME = cub3D

SRC = src/main.c \
	src/animation.c \
	src/dda_init_values.c \
	src/dda.c src/doors.c \
	src/draw_frame_utils.c \
	src/draw_frame.c \
	src/init.c \
	src/key_hooks.c \
	src/minimap.c \
	src/movements.c \
	src/movements_utils.c \
	src/ray_casting.c \
	src/rotation.c \
	src/wall_height.c \
	src/exit_prog.c \
	src/parsing/read_utils.c \
	src/parsing/free_close_exit.c \
	src/parsing/map_utils.c \
	src/parsing/parse_utils.c \
	src/parsing/parsing.c

OBJ = ${SRC:.c=.o}

MLXLIB = ./minilibx-linux/libmlx_Linux.a

LIBFT = ./src/libft/libft.a

all: $(LIBFT) $(MLXLIB) $(NAME) 

$(MLXLIB):
	make -C minilibx-linux/

$(LIBFT):
	make -C ./src/libft/

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXLIB) $(LIBFT) -Lmlx_linux  -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) -g #-fsanitize=address

%.o: %.c includes/cub3d.h src/libft/libft.h
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@ -g #-fsanitize=address

clean:
	rm -rf $(OBJ)
	make clean -C minilibx-linux/
	make clean -C ./src/libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./src/libft

re: fclean all