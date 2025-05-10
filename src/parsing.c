/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:58 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/05 17:48:46 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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

static int	check_map_file(const char *file_name)
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
		exit(10);
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

void	free_elems(t_elements *elems, char *error)
{
	size_t	i;

	if (elems->north_file)
		free(elems->north_file);
	if (elems->south_file)
		free(elems->south_file);
	if (elems->west_file)
		free(elems->west_file);
	if (elems->east_file)
		free(elems->east_file);
	if (elems->map)
	{
		i = -1;
		while (++i < elems->rows)
			free(elems->map[i]);
		free(elems->map);
	}
	if (elems->fd != 0)
		close(elems->fd);
	printf("Error\n%s\n", error);
	exit(53);
}

void	parse_texture(t_elements *elems, char **texture, char *line, int j)
{
	while (ft_isspace(line[j]))
		j++;
	*texture = ft_substr(&line[j], 0, ft_strlen(&line[j]));
	if (*texture == NULL)
	{
		free(line);
		free_elems(elems, GENERIC_ERR_MSG);
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
void	parse_colors(t_elements *elems, char *line, char flag, int j)
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
			elems->floor_rgb |= (value << (16 - i * 8));
		else if (error == 0 && flag == CEILING)
			elems->ceil_rgb |= (value << (16 - i * 8));
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
void	read_elements(t_elements *elems)
{
	int		i;
	int		j;
	char	*line;

	i = 6;
	while (i--)
	{
		line = read_valid_line(elems->fd);
		j = -1;
		while (line[++j] && ft_isspace(line[j]))
			;
		if (line[j] == 'N' && line[++j] == 'O' && line[++j] == ' ')
			parse_texture(elems, &elems->north_file, line, j);
		else if (line[j] == 'S' && line[++j] == 'O' && line[++j] == ' ')
			parse_texture(elems, &elems->south_file, line, j);
		else if (line[j] == 'W' && line[++j] == 'E' && line[++j] == ' ')
			parse_texture(elems, &elems->west_file, line, j);
		else if (line[j] == 'E' && line[++j] == 'A' && line[++j] == ' ')
			parse_texture(elems, &elems->east_file, line, j);
		else if ((line[j] == 'F' || line[j] == 'C') && line[++j] == ' ')
			parse_colors(elems, line, line[j - 1], j);
		else
			invalid_element_error(line, elems->fd);
		free(line);
	}
}

// the subject never metions \t \r \v so maybe should not be handled. only new lines and and spaces should be handled
char	*read_first_valid_row(t_elements *elems)
{
	int		i;
	char	*line;

	line = get_next_line_wrapper(elems->fd);
	if (line == NULL)
		free_elems(elems, MAP_ERR_MSG);
	while (line)
	{
		i = -1;
		while (line[++i])
		{
			if (!ft_isspace(line[i]))
				return (line);
		}
		free(line);
		line = get_next_line_wrapper(elems->fd);
		if (line == NULL)
			break ;
	}
	free_elems(elems, MAP_ERR_MSG);
	return (NULL);
}

size_t	count_trailing_spaces(char *line)
{
	int		i;
	size_t	trailing_spaces;

	trailing_spaces = 0;
	i = ft_strlen(line) - 1;
	while (line[i--] == ' ')
		trailing_spaces++;
	return (trailing_spaces);
}

/* is count trailing spaces really needed?
 needed because map row can be like "11111          "	column size 15
 								      "1000111111" 		column size 10
    								  "100000000111"	column size 12 Should allocate this for all cols
								      "1111111111"		column size 10
the spaces don't make the map invalid in this case but we should not include those spaces in counting the longest column
*/
void	count_layouts(t_elements *elems)
{
	char	*line;
	int		empty;
	int		flag;
	int		i;

	empty = 0;
	line = read_first_valid_row(elems);
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
		elems->rows++;
		if (elems->cols < ft_strlen(line) - count_trailing_spaces(line))
			elems->cols = ft_strlen(line) - count_trailing_spaces(line);
		line = get_next_line_wrapper(elems->fd);
	}
	if (elems->cols == 0 || elems->rows == 0)
		free_elems(elems, MAP_ERR_MSG);
	elems->rows -= empty;
}

void	allocate_map_array(t_elements *elems)
{
	size_t	i;

	elems->map = malloc(sizeof(char *) * elems->rows);
	if (elems->map == NULL)
		free_elems(elems, GENERIC_ERR_MSG);
	ft_memset(elems->map, 0, sizeof(char *) * elems->rows);
	i = 0;
	while (i < elems->rows)
	{
		elems->map[i] = malloc(elems->cols + 1);
		if (elems->map[i] == NULL)
		{
			while (i--)
			{
				free(elems->map[i]);
				elems->map[i] = NULL;
			}
			free_elems(elems, GENERIC_ERR_MSG);
		}
		ft_memset(elems->map[i], 0, elems->cols + 1);
		i++;
	}
}

void	skip_initial_data(t_elements *elems)
{
	size_t	i;
	char	*line;

	i = 0;
	while (++i < number_of_invocations(2))
	{
		line = get_next_line_wrapper(elems->fd);
		if (line == NULL)
		{
			free(line);
			free_elems(elems, GENERIC_ERR_MSG);
		}
		free(line);
	}
}

void	copy_each_row(t_elements *elems, char *line, size_t i, size_t *j)
{
	static int	flag;

	while (++(*j) < ft_strlen(line))
	{
		if (ft_strchr("10NSEW ", line[*j]))
		{
			if (ft_strchr("NSEW", line[*j]) && flag == 0)
			{
				elems->player_row = i;
				elems->player_col = *j;
				flag = 1;
			}
			else if (ft_strchr("NSEW", line[*j]) && flag == 1)
				free_elems(elems, MAP_ERR_MSG);
			elems->map[i][*j] = line[*j];
		}
		else
			free_elems(elems, MAP_ERR_MSG);
	}
}

void	parse_map(t_elements *elems)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = -1;
	skip_initial_data(elems);
	allocate_map_array(elems);
	while (++i < elems->rows)
	{
		line = get_next_line_wrapper(elems->fd);
		if (line == NULL)
		{
			// the snumbers should be correct to not exit when there is a valid map
			free_elems(elems, GENERIC_ERR_MSG);
		}
		j = -1;
		copy_each_row(elems, line, i, &j);
		while (j < elems->cols)
			elems->map[i][j++] = EMPTY;
	}
}

// check right then left
bool	check_horizontally(t_elements *elems, size_t i, size_t j)
{
	const size_t	row = i;
	const size_t	col = j;

	while (++j < elems->cols)
	{
		if (elems->map[row][j] == WALL)
			break ;
		if (j + 1 == elems->cols || elems->map[row][j + 1] == EMPTY)
		{
			printf("\tinvalidated by 1\n");
			return (true);
		}
	}
	j = col;
	while (j)
	{
		j--;
		if (elems->map[row][j] == WALL)
			break ;
		if (j == 0 || elems->map[row][j - 1] == EMPTY)
		{
			printf("\tinvalidated by 2\n");
			return (true);
		}
	}
	return (false);
}

// check down and then up
bool	check_vertically(t_elements *elems, size_t i, size_t j)
{
	const size_t	row = i;
	const size_t	col = j;

	while (++i < elems->rows)
	{
		if (elems->map[i][col] == WALL)
			break ;
		if (i + 1 == elems->rows || elems->map[i + 1][col] == EMPTY)
		{
			printf("\tinvalidated by 3\n");
			return (true);
		}
	}
	i = row;
	while (i)
	{
		i--;
		if (elems->map[i][col] == WALL)
			break ;
		if (i == 0 || elems->map[i - 1][col] == EMPTY)
		{
			printf("\tinvalidated by 4\n");
			return (true);
		}
	}
	return (false);
}

// there many ways to detect leaks to outside world; chose easiest but complexit is around ~ O(n^3) 
// can be optimized though
// also can do BFS DFS and other fancy stuff to just check the outer walls but that's beyond my abilities right now
// we can optimize it later; be done with parsing asap to focus on ray casting and other stuff
void	check_map(t_elements *elems)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < elems->rows)
	{
		j = -1;
		while (++j < elems->cols)
		{
			if (ft_strchr("NSEW0", elems->map[i][j]))
			{
				if (check_vertically(elems, i, j)
					|| check_horizontally(elems, i, j))
					free_elems(elems, MAP_ERR_MSG);
			}
		}
	}
}

void	parse_file(t_elements *elems, const char *file_name)
{
	elems->fd = check_map_file(file_name);
	read_elements(elems);
	count_layouts(elems);
	close(elems->fd);

	elems->fd = check_map_file(file_name);
	parse_map(elems);
	check_map(elems);
	close(elems->fd);
}

// void	print_my_elems(t_elements *elems)
// {
// 	printf("north_file:\t[%s]\n", elems->north_file);
// 	printf("south_file:\t[%s]\n", elems->south_file);
// 	printf("east_file:\t[%s]\n", elems->east_file);
// 	printf("west_file:\t[%s]\n", elems->west_file);
// 	printf("floor_rgb:\t[%#x]\n", elems->floor_rgb);
// 	printf("ceil_rgb:\t[%#x]\n\n", elems->ceil_rgb);
// 	printf("x|");
// 	for (size_t k = 0; k < elems->cols; k++)
// 		printf("%zu", k % 10);
// 	printf("\n");
// 	printf("x|");
// 	for (size_t k = 0; k < elems->cols; k++)
// 		printf("=");
// 	printf("\n");
// 	for (size_t i = 0; i < elems->rows; i++)
// 	{
// 		printf("%zu|", i % 10);
// 		for (size_t j = 0; j < elems->cols; j++)
// 			printf("%c", elems->map[i][j]);
// 		printf("\n");
// 	}
// 	printf("\nPlayer: %c (%zu, %zu)\n", elems->map[elems->player_row - 1][elems->player_col - 1], elems->player_col, elems->player_row);
// }

// int main(int argc, char *argv[])
// {
// 	t_elements	elems;

// 	if (argc != 2)
// 	{
// 		printf("Error\nUsage: ./bin map.cub\n");
// 		return (1);
// 	}
// 	ft_memset(&elems, 0, sizeof(t_elements));
// 	parse_file(&elems, argv[1]);
// 	printf("Go Next Step\n");
// 	print_my_elems(&elems);
// }