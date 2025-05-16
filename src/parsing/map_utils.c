/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:45:37 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/16 18:16:54 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_horiz(t_info *info, ssize_t i, ssize_t j)
{
	const ssize_t	row = i;
	const ssize_t	col = j;

	while (++j < info->map_w)
	{
		if (info->map[row][j] == WALL)
			break ;
		if (j + 1 == info->map_w || info->map[row][j + 1] == EMPTY)
			return (true);
	}
	j = col;
	while (j)
	{
		j--;
		if (info->map[row][j] == WALL)
			break ;
		if (j == 0 || info->map[row][j - 1] == EMPTY)
			return (true);
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
			return (true);
	}
	i = row;
	while (i)
	{
		i--;
		if (info->map[i][col] == WALL)
			break ;
		if (i == 0 || info->map[i - 1][col] == EMPTY)
			return (true);
	}
	return (false);
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
				free_and_exit(info, line, MAP_ERR_MSG);
			if (line[*j] == '2')
				info->n_doors++;
			info->map[i][*j] = line[*j];
		}
		else
			free_and_exit(info, line, MAP_ERR_MSG);
	}
	return (flag);
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
