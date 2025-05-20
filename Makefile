NAME = cub3D

LIBFTSRCS = src/libft/ft_atoi.c \
		src/libft/ft_bzero.c \
		src/libft/ft_calloc.c \
		src/libft/ft_isalnum.c \
		src/libft/ft_isalpha.c \
		src/libft/ft_isascii.c \
		src/libft/ft_isdigit.c \
		src/libft/ft_isprint.c \
		src/libft/ft_itoa.c \
		src/libft/ft_memchr.c \
		src/libft/ft_memcmp.c \
		src/libft/ft_memcpy.c \
		src/libft/ft_memmove.c \
		src/libft/ft_memset.c \
		src/libft/ft_putchar_fd.c \
		src/libft/ft_putendl_fd.c \
		src/libft/ft_putnbr_fd.c \
		src/libft/ft_putstr_fd.c \
		src/libft/ft_split.c \
		src/libft/ft_strchr.c \
		src/libft/ft_strdup.c \
		src/libft/ft_striteri.c \
		src/libft/ft_strjoin.c \
		src/libft/ft_strlcat.c \
		src/libft/ft_strlcpy.c \
		src/libft/ft_strlen.c \
		src/libft/ft_strmapi.c \
		src/libft/ft_strncmp.c \
		src/libft/ft_strnstr.c \
		src/libft/ft_strrchr.c \
		src/libft/ft_strtrim.c \
		src/libft/ft_substr.c \
		src/libft/ft_tolower.c \
		src/libft/ft_toupper.c \
		src/libft/get_next_line.c \
		src/libft/get_next_line_utils.c

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

$(LIBFT): $(LIBFTSRCS) src/libft/libft.h
	make -C ./src/libft/

$(NAME): $(OBJ) $(LIBFTSRCS) src/libft/libft.h
	$(CC) -Wall -Wextra -Werror -g -fsanitize=address $(OBJ) $(MLXLIB) $(LIBFT) -Lmlx_linux  -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c includes/cub3d.h src/libft/libft.h
	$(CC) -Wall -Wextra -Werror -g -fsanitize=address -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(OBJ)
	make clean -C minilibx-linux/
	make clean -C ./src/libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./src/libft

re: fclean all