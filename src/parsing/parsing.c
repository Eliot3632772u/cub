/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:58 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/18 08:10:39 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
					free_and_exit(info, NULL, MAP_ERR_MSG);
				if (info->map[i][j] == '2' && handle_door(info, i, j))
					free_and_exit(info, NULL, MAP_ERR_MSG);
			}
		}
	}
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
		free_and_exit(info, NULL, MAP_ERR_MSG);
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
			free_and_exit(info, line, MAP_ERR_MSG);
		if (info->map_w < ft_strlen(line) - count_trailing_spaces(line))
			info->map_w = ft_strlen(line) - count_trailing_spaces(line);
		free(line);
		line = get_next_line_wrapper(info->fd);
	}
	if (info->map_w == 0 || info->map_h == 0)
		free_and_exit(info, NULL, MAP_ERR_MSG);
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
			free_and_exit(info, line, "Map file misconfigured");
		free(line);
	}
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
