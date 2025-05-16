/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:58 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/16 14:50:23 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_allocs(t_info *info, char *alloc)
{
	int	i;

	if (alloc)
		free(alloc);
	if (info->north)
		free(info->north);
	if (info->south)
		free(info->south);
	if (info->east)
		free(info->east);
	if (info->west)
		free(info->west);
	if (info->doors)
		free(info->doors);
	if (info->map)
	{
		i = -1;
		while (++i < info->map_h)
			free(info->map[i]);
		free(info->map);
	}
}

void	close_fd(int fd)
{
	if (fd > 0)
	{
		close(fd);
	}
}

void	destroy_mlx(t_info *info)
{
	mlx_destroy_image(info->mlx.con, info->mlx.img);
	mlx_destroy_window(info->mlx.con, info->mlx.win);
	mlx_destroy_display(info->mlx.con);
	free(info->mlx.con);
}

void	free_and_exit(t_info *info, char *alloc, char *error_msg)
{
	destroy_mlx(info);
	close_fd(info->fd);
	free_allocs(info, alloc);
	if (error_msg)
	{
		printf("Error\n%s\n", error_msg);
		exit(1);
	}
	exit(0);
}

size_t	number_of_invocations(int flag)
{
	static size_t	number = 0;
	static size_t	actual = 0;

	if (flag == 0)
		number++;
	else if (flag == 1)
		actual = number;
	return (actual);
}

char	*get_next_line_wrapper(int fd)
{
	char	*line;
	char	*line_without_newline;

	
	line = get_next_line(fd);
	number_of_invocations(0);
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

int	check_name(t_info *info)
{
	const char	*ends_with = ".cub";
	int			fd;
	int			i;
	int			j;

	i = ft_strlen(info->file_name);
	j = ft_strlen(ends_with);
	while (i && j && info->file_name[i] == ends_with[j])
	{
		i--;
		j--;
	}
	if (j != 0)
		free_and_exit(info, NULL, "Doesn't end with .cub");
	fd = open(info->file_name, O_RDONLY);
	if (fd == -1)
		free_and_exit(info, NULL, "Bad map file");
	return (fd);
}

char	*read_valid_line(t_info *info)
{
	int		i;
	char	*line;

	while (true)
	{
		line = get_next_line_wrapper(info->fd);
		if (line == NULL)
			free_and_exit(info, NULL, "Invalid map elements");
		i = -1;
		while (line[++i])
		{
			if (line[i] != ' ')
				return (line);
		}
		free(line);
	}
	return (NULL);
}

void	parse_texture(t_info *info, char **texture, char *line, int j)
{
	while (line[j] == ' ')
		j++;
	*texture = ft_substr(&line[j], 0, ft_strlen(&line[j]));
	if (*texture == NULL)
	{
		free_and_exit(info, line, GENERIC_ERR_MSG);
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

void	ft_color_error(char *line)
{
	printf("Error\nBad floor/ceiling colors\n");
	(void)line;
	exit(44);
}

char	*get_next_part(char *line, int *j)
{
	int	i;
	int	k;

	i = 0;
	while (line[*j] == ' ')
		(*j)++;
	k = *j;
	while (line[i + *j] && ft_isdigit(line[i + *j]) && i < 3)
		i++;
	if (i == 0)
		return (NULL);
	*j += i;
	while (line[*j] && line[*j] == ' ')
		(*j)++;
	if (line[*j] != ',' && line[*j] != '\0')
		return (NULL);
	(*j)++;
	return (ft_substr(&line[k], 0, i));
}

void	parse_colors(t_info *info, char *line, char flag, int j)
{
	int		i;
	int		value;
	int		error;
	char	*part;
	
	i = -1;
	while (++i < 3)
	{
		part = get_next_part(line, &j);
		if (part == NULL)
			free_and_exit(info, line, GENERIC_ERR_MSG);
		error = 0;
		value = ft_atoi(part, &error);
		if (error == 0 && flag == FLOOR)
			info->mlx.flr_clr |= (value << (16 - i * 8));
		else if (error == 0 && flag == CEILING)
			info->mlx.cel_clr |= (value << (16 - i * 8));
		else
		{
			free(part);
			free_and_exit(info, line, "Bad colors configuration");
		}
		free(part);
	}
}

void	read_elements(t_info *info)
{
	int		i;
	int		j;
	char	*line;

	i = 6;
	while (i--)
	{
		line = read_valid_line(info);
		j = -1;
		while (line[++j] && line[j] == ' ')
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
			free_and_exit(info, line, "Bad map file");
		free(line);
	}
}

ssize_t	count_trailing_spaces(char *line)
{
	ssize_t	i;
	ssize_t	trailing_spaces;

	trailing_spaces = 0;
	i = ft_strlen(line) - 1;
	while (i > -1 && line[i--] == ' ')
		trailing_spaces++;
	return (trailing_spaces);
}

bool	has_more_valid_lines(t_info *info)
{
	char	*line;
	int		i;

	while (true)
	{
		line = get_next_line_wrapper(info->fd);
		if (line == NULL)
			return (false);
		i = -1;
		while (line[++i])
		{
			if (line[i] != ' ')
			{
				free(line);	
				return (true);
			}
		}
		free(line);
	}
	return (false);
}

void	count_layouts(t_info *info)
{
	char	*line;
	int		flag;
	int		i;

	line = read_valid_line(info);
	number_of_invocations(1);
	while (line)
	{
		flag = 0;
		i = -1;
		while (line[++i])
			if (line[i] != ' ')
				flag = 1;
		if (flag == 1)
			info->map_h++;
		else if (flag == 0 && has_more_valid_lines(info))
			free_and_exit(info, line, "HELL 0");
		if (info->map_w < ft_strlen(line) - count_trailing_spaces(line))
			info->map_w = ft_strlen(line) - count_trailing_spaces(line);
		free(line);
		line = get_next_line_wrapper(info->fd);
	}
	if (info->map_w == 0 || info->map_h == 0)
		free_and_exit(info, NULL, "HELL 1");
}

void	allocate_map_array(t_info *info)
{
	ssize_t	i;

	info->map = malloc(sizeof(char *) * info->map_h);
	if (info->map == NULL)
		free_and_exit(info, NULL, GENERIC_ERR_MSG);
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
			free(info->map);
			info->map = NULL;
			free_and_exit(info, NULL, GENERIC_ERR_MSG);
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
			free_and_exit(info, NULL, GENERIC_ERR_MSG);
		free(line);
	}
}

int	copy_each_row(t_info *info, char *line, ssize_t i, ssize_t *j)
{
	static int	flag;

	while (++(*j) < info->map_w && *j < ft_strlen(line))
	{
		if (ft_strchr("210NSEW ", line[*j]))
		{
			if (ft_strchr("NSEW", line[*j]) && flag == 0)
			{
				info->p_x = *j;
				info->p_y = i;
				flag = 1;
			}
			else if (ft_strchr("NSEW", line[*j]) && flag == 1)
				free_and_exit(info, line, "HELL 2");
			if (line[*j] == '2')
				info->n_doors++;
			info->map[i][*j] = line[*j];
		}
		else
			free_and_exit(info, line, "HELL 3");
	}
	return (flag);
}

void	parse_map(t_info *info)
{
	ssize_t	i;
	ssize_t	j;
	char	*line;
	int		flag;

	flag = 0;
	skip_initial_data(info);
	allocate_map_array(info);
	i = -1;
	while (++i < info->map_h)
	{
		line = get_next_line_wrapper(info->fd);
		if (line == NULL)
			free_and_exit(info, NULL, GENERIC_ERR_MSG);
		j = -1;
		flag = copy_each_row(info, line, i, &j);
		while (j < info->map_w)
			info->map[i][j++] = EMPTY;
		free(line);
	}
	if (flag == 0)
		free_and_exit(info, NULL, "HELL 4");
}

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
			return (true);
		flag = 0;
	}
	if (i == 0 || j == 0 || i + 1 == info->map_h || i + 1 == info->map_w)
		return (true);
	between_h = info->map[i][j - 1] == '1' && info->map[i][j + 1] == '1';
	between_v = info->map[i - 1][j] == '1' && info->map[i - 1][j] == '1';
	if (!between_h && !between_v)
		return (true);
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
					free_and_exit(info, NULL, "HELL 5");
				if (info->map[i][j] == '2' && handle_door(info, i, j))
					free_and_exit(info, NULL, "HELL 6");
			}
		}
	}
}

double	select_angle(t_info *info)
{
	if (info->map[info->p_y][info->p_x] == 'N')
		return(deg_to_rad(270));
	else if (info->map[info->p_y][info->p_x] == 'S')
		return(deg_to_rad(90));
	else if (info->map[info->p_y][info->p_x] == 'E')
		return(deg_to_rad(0));
	else
		return(deg_to_rad(180));
}

void	parse_file(t_info *info)
{
	info->fd = -1;
	info->fd = check_name(info);
	read_elements(info);
	count_layouts(info);
	close(info->fd);
	info->fd = -1;
	info->fd = check_name(info);
	parse_map(info);
	close(info->fd);
	info->fd = -1;
	check_map(info);
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
	printf("\nPlayer: %c (%zu, %zu)\n", info->map[info->p_y][info->p_x], info->p_x, info->p_y);
	int z = -1;
	printf("Num of doors: %d\n", info->n_doors);
	while (++z < info->n_doors)
	{
		printf("(%i, %i)", info->doors[z].door_x, info->doors[z].door_y);
	}
}
