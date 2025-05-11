/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:58 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/11 11:13:56 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_next_line_wrapper(int fd)
{
	char	*line;
	char	*line_without_newline;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
	{
		line_without_newline = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		return (line_without_newline);
	}
	else
		return (line);
}

static int	check_name(const char *file_name)
{
	const char	*ends_with = ".cub";
	int			fd;
	int			i;
	int			j;

	i = ft_strlen(file_name);
	j = ft_strlen(ends_with);
	while (i && j && file_name[i] == ends_with[j])
	{
		i--;
		j--;
	}
	if (j != 0)
	{
		printf("Error\nBad map file: does not end with .cub\n");
		exit(10); // should not init mlx before this
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Erorr\nBad map file");
		exit(11);
	}
	return (fd);
}

// maybe should check just spaces = ascii 32
static char	*read_valid_line(int fd)
{
	int		i;
	char	*line;

	line = get_next_line_wrapper(fd);
	if (line == NULL)
	{
		printf("Error\nInvalid map elements\n");
		exit (close(fd) + 42);
	}
	while (line)
	{
		i = -1;
		while (line[++i])
		{
			if (!ft_isspace(line[i]))
				return (line);
		}
		line = get_next_line_wrapper(fd);
		if (line == NULL)
		{
			printf("Error\nInvalid map elements\n");
			exit (close(fd) + 42);
		}
	}
	return (NULL);
}

void	free_elems(t_info *info, char *error)
{
	int	i;

	if (info->north)
		free(info->north);
	if (info->south)
		free(info->south);
	if (info->west)
		free(info->west);
	if (info->east)
		free(info->east);
	if (info->map)
	{
		i = -1;
		while (++i < info->map_h)
			free(info->map[i]);
		free(info->map);
	}
	if (info->fd != 0)
		close(info->fd);
	printf("Error\n%s\n", error);
	exit(53);
}

void	parse_texture(t_info *info, char **texture, char *line, int j)
{
	while (ft_isspace(line[j]))
		j++;
	*texture = ft_substr(&line[j], 0, ft_strlen(&line[j]));
	if (*texture == NULL)
	{
		free(line);
		free_elems(info, GENERIC_ERR_MSG);
	}
}

void	free_2d(char **array)
{
	int	i;

	if (array)
	{
		i = -1;
		while (array[++i])
			free(array[i]);
		free(array);
	}
}

void	ft_color_error(char **array)
{
	printf("Error\nBad floor/ceiling colors\n");
	free_2d(array);
	exit(44);
}

// atoi would not work in case of number followed by space: 225,30 ,0
// fix atoi or ft_split to take delimiters ", "
// also using split for other part of the code might be better
void	parse_colors(t_info *info, char *line, char flag, int j)
{
	int		i;
	int		value;
	int		error;
	char	**array;

	while (ft_isspace(line[j]))
		j++;
	array = ft_split(&line[j], ',');
	i = -1;
	while (array[++i])
	{
		error = 0;
		value = ft_atoi(array[i], &error);
		if (error == 0 && flag == FLOOR)
			info->mlx.flr_clr |= (value << (16 - i * 8));
		else if (error == 0 && flag == CEILING)
			info->mlx.cel_clr |= (value << (16 - i * 8));
		else
			ft_color_error(array);
	}
	if (i != 3)
		ft_color_error(array);
	free_2d(array);
}

void	invalid_element_error(char *line, int fd)
{
	printf("Error\nBad map file\n");
	free(line);
	exit(close(fd) + 43);
}

// better use strncmp in all these and maybe info can be seperated by "\t\n\v\..."
void	read_elements(t_info *info)
{
	int		i;
	int		j;
	char	*line;

	i = 6;
	while (i--)
	{
		line = read_valid_line(info->fd);
		j = -1;
		while (line[++j] && ft_isspace(line[j]))
			;
		if (line[j] == 'N' && line[++j] == 'O' && line[++j] == ' ')
			parse_texture(info, &info->north, line, j);
		else if (line[j] == 'S' && line[++j] == 'O' && line[++j] == ' ')
			parse_texture(info, &info->south, line, j);
		else if (line[j] == 'W' && line[++j] == 'E' && line[++j] == ' ')
			parse_texture(info, &info->west, line, j);
		else if (line[j] == 'E' && line[++j] == 'A' && line[++j] == ' ')
			parse_texture(info, &info->east, line, j);
		else if ((line[j] == 'F' || line[j] == 'C') && line[++j] == ' ')
			parse_colors(info, line, line[j - 1], j);
		else
			invalid_element_error(line, info->fd);
		free(line);
	}
}

// the subject never metions \t \r \v so maybe should not be handled. only new lines and and spaces should be handled
char	*read_first_valid_row(t_info *info)
{
	int		i;
	char	*line;

	line = get_next_line_wrapper(info->fd);
	if (line == NULL)
		free_elems(info, MAP_ERR_MSG);
	while (line)
	{
		i = -1;
		while (line[++i])
		{
			if (!ft_isspace(line[i]))
				return (line);
		}
		free(line);
		line = get_next_line_wrapper(info->fd);
		if (line == NULL)
			break ;
	}
	free_elems(info, MAP_ERR_MSG);
	return (NULL);
}

ssize_t	count_trailing_spaces(char *line)
{
	int		i;
	size_t	trailing_spaces;

	trailing_spaces = 0;
	i = ft_strlen(line) - 1;
	while (i > -1 && line[i--] == ' ')
		trailing_spaces++;
	return (trailing_spaces);
}

void	count_layouts(t_info *info)
{
	char	*line;
	int		empty;
	int		flag;
	int		i;

	empty = 0;
	line = read_first_valid_row(info);
	number_of_invocations(1);
	while (line)
	{
		flag = 0;
		i = -1;
		while (line[++i])
			if (!ft_isspace(line[i]))
				flag = 1;
		if (flag == 0)
			empty++;
		info->map_h++;
		if (info->map_w < ft_strlen(line) - count_trailing_spaces(line))
			info->map_w = ft_strlen(line) - count_trailing_spaces(line);
		free(line);
		line = get_next_line_wrapper(info->fd);
	}
	if (info->map_w == 0 || info->map_h == 0)
		free_elems(info, MAP_ERR_MSG);
	info->map_h -= empty;
	printf("map_h: %i map_w: %i\n", info->map_h, info->map_w);
}

void	allocate_map_array(t_info *info)
{
	ssize_t	i;

	info->map = malloc(sizeof(char *) * info->map_h);
	if (info->map == NULL)
		free_elems(info, GENERIC_ERR_MSG);
	ft_memset(info->map, 0, sizeof(char *) * info->map_h);
	i = 0;
	while (i < info->map_h)
	{
		info->map[i] = malloc(info->map_w);
		if (info->map[i] == NULL)
		{
			while (i--)
			{
				free(info->map[i]);
				info->map[i] = NULL;
			}
			free_elems(info, GENERIC_ERR_MSG);
		}
		ft_memset(info->map[i], 0, info->map_w);
		i++;
	}
}

void	skip_initial_data(t_info *info)
{
	size_t	i;
	char	*line;

	i = 0;
	while (++i < number_of_invocations(2))
	{
		line = get_next_line_wrapper(info->fd);
		if (line == NULL)
		{
			free(line);
			free_elems(info, GENERIC_ERR_MSG);
		}
		free(line);
	}
}

void	copy_each_row(t_info *info, char *line, ssize_t i, ssize_t *j)
{
	static int	flag;

	while (++(*j) < info->map_w && *j < ft_strlen(line))
	{
		if (ft_strchr("210NSEW ", line[*j]))
		{
			if (ft_strchr("NSEW", line[*j]) && flag == 0)
			{
				info->p_x = i;
				info->p_y = *j;
				flag = 1;
			}
			else if (ft_strchr("NSEW", line[*j]) && flag == 1)
				free_elems(info, MAP_ERR_MSG);
			if (line[*j] == '2')
			{
				info->n_doors++;
				printf("Number of doors: %d\n", info->n_doors);
			}
			info->map[i][*j] = line[*j];
		}
		else
			free_elems(info, MAP_ERR_MSG);
	}
}

void	parse_map(t_info *info)
{
	ssize_t	i;
	ssize_t	j;
	char	*line;

	skip_initial_data(info);
	allocate_map_array(info);
	i = -1;
	while (++i < info->map_h)
	{
		line = get_next_line_wrapper(info->fd);
		if (line == NULL)
			free_elems(info, GENERIC_ERR_MSG);
		j = -1;
		copy_each_row(info, line, i, &j);
		while (j < info->map_w)
			info->map[i][j++] = EMPTY;
		free(line);
	}
}

// check right then left
bool	check_horiz(t_info *info, ssize_t i, ssize_t j)
{
	const ssize_t	row = i;
	const ssize_t	col = j;

	while (++j < info->map_w)
	{
		if (info->map[row][j] == WALL)
			break ;
		if (j + 1 == info->map_w || info->map[row][j + 1] == EMPTY)
		{
			printf("\tinvalidated by 1\n");
			return (true);
		}
	}
	j = col;
	while (j)
	{
		j--;
		if (info->map[row][j] == WALL)
			break ;
		if (j == 0 || info->map[row][j - 1] == EMPTY)
		{
			printf("\tinvalidated by 2\n");
			return (true);
		}
	}
	return (false);
}

// check down and then up
bool	check_vert(t_info *info, ssize_t i, ssize_t j)
{
	const ssize_t	row = i;
	const ssize_t	col = j;

	while (++i < info->map_h)
	{
		if (info->map[i][col] == WALL)
			break ;
		if (i + 1 == info->map_h || info->map[i + 1][col] == EMPTY)
		{
			printf("\tinvalidated by 3\n");
			return (true);
		}
	}
	i = row;
	while (i)
	{
		i--;
		if (info->map[i][col] == WALL)
			break ;
		if (i == 0 || info->map[i - 1][col] == EMPTY)
		{
			printf("\tinvalidated by 4\n");
			return (true);
		}
	}
	return (false);
}

bool	handle_door(t_info *info, ssize_t i, ssize_t j)
{
	static int	flag = -1;
	bool		between_h;
	bool		between_v;

	if (flag == -1)
	{
		info->doors = malloc(sizeof(t_door) * info->n_doors);
		if (info->doors == NULL)
			free_elems(info, GENERIC_ERR_MSG);
		flag = 0;
	}
	if (i == 0 || j == 0 || i + 1 == info->map_h || i + 1 == info->map_w)
	{
		printf("1\n");
		return (true);
	}
	between_h = info->map[i][j - 1] == '1' && info->map[i][j + 1] == '1';
	between_v = info->map[i - 1][j] == '1' && info->map[i - 1][j] == '1';
	if (!between_h && !between_v)
	{
		printf("2\n");
		return (true);
	}
	info->doors[flag].door_x = j;
	info->doors[flag].door_y = i;
	info->doors[flag].is_open = 0;
	flag++;
	return (false);
}

void	check_map(t_info *info)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (++i < info->map_h)
	{
		j = -1;
		while (++j < info->map_w)
		{
			if (ft_strchr("20NSEW", info->map[i][j]))
			{
				if (check_vert(info, i, j) || check_horiz(info, i, j))
					free_elems(info, MAP_ERR_MSG);
				if (info->map[i][j] == '2' && handle_door(info, i, j))
					free_elems(info, "test2");
			}
		}
	}
}

void	parse_file(t_info *info)
{
	info->fd = check_name(info->file_name);
	read_elements(info);
	count_layouts(info);
	close(info->fd);

	info->fd = check_name(info->file_name);
	parse_map(info);
	check_map(info);
	close(info->fd);
}

void	init_map_data(t_info *info)
{
	info->map_h = 0;
	info->map_w = 0;
	info->mlx.cel_clr = 0;
    info->mlx.flr_clr = 0;
	info->map = NULL;
	info->north = NULL;
	info->south = NULL;
	info->east = NULL;
	info->west = NULL;
	info->doors = NULL;
	info->n_doors = 0;
    parse_file(info);
	info->player.pX = info->p_x * info->TILE_SIZE;
    info->player.pY = info->p_y * info->TILE_SIZE;
	if (info->map[info->p_y][info->p_x] == 'N')
		info->player.angle = deg_to_rad(90);
	else if (info->map[info->p_y][info->p_x] == 'S')
		info->player.angle = deg_to_rad(270);
	else if (info->map[info->p_y][info->p_x] == 'E')
		info->player.angle = deg_to_rad(180);
	else if (info->map[info->p_y][info->p_x] == 'W')
		info->player.angle = deg_to_rad(0);
	init_tex(info);
	print_my_elems(info);
}

void	free_all(t_info *info)
{
	free(info->north);
	free(info->south);
	free(info->east);
	free(info->west);
	if (info->doors)
		free(info->doors);
	ssize_t i = -1;
	while (++i < info->map_h)
	{
		free(info->map[i]);
	}
	free(info->map);
}

void	print_my_elems(t_info *info)
{
	printf("north_file:\t[%s]\n", info->north);
	printf("south_file:\t[%s]\n", info->south);
	printf("east_file:\t[%s]\n", info->east);
	printf("west_file:\t[%s]\n", info->west);
	printf("floor_rgb:\t[%#x]\n", info->mlx.flr_clr);
	printf("ceil_rgb:\t[%#x]\n\n", info->mlx.cel_clr);
	printf("x|");
	for (ssize_t k = 0; k < info->map_w; k++)
		printf("%zu", k % 10);
	printf("\n");
	printf("x|");
	for (ssize_t k = 0; k < info->map_w; k++)
		printf("=");
	printf("\n");
	for (ssize_t i = 0; i < info->map_h; i++)
	{
		printf("%zu|", i % 10);
		for (ssize_t j = 0; j < info->map_w; j++)
			printf("%c", info->map[i][j]);
		printf("\n");
	}
	printf("\nPlayer: %c (%zu, %zu)\n", info->map[info->p_x - 1][info->p_y - 1], info->p_x, info->p_y);
	int z = -1;
	printf("Num of doors: %d\n", info->n_doors);
	while (++z < info->n_doors)
	{
		printf("(%i, %i)", info->doors[z].door_x, info->doors[z].door_y);
	}
	free_all(info);
}

// int main(int ac, char *av[])
// {
// 	t_info	info;

// 	if (ac != 2)
// 	{
// 		printf("Error\nUsage: ./bin map.cub\n");
// 		return (1);
// 	}
// 	info.file_name = av[1];
// 	init_map_data(&info);
// 	printf("Go Next Step\n");
// 	print_my_elems(&info);
// }