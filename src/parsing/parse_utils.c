/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:50:43 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/18 08:07:55 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	if (j != 0 || info->file_name[i] != ends_with[j])
		free_and_exit(info, NULL, "Doesn't end with .cub");
	fd = open(info->file_name, O_RDONLY);
	if (fd == -1)
		free_and_exit(info, NULL, "Cannot open file");
	return (fd);
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
	j++;
	while (++i < 3)
	{
		part = get_next_part(line, &j);
		if (part == NULL)
			free_and_exit(info, line, "Bad colors configuration");
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
	between_h = (info->map[i][j - 1] == '1' && info->map[i][j + 1] == '1');
	between_v = (info->map[i - 1][j] == '1' && info->map[i - 1][j] == '1');
	if (!between_h && !between_v)
		return (true);
	info->doors[flag].door_x = j;
	info->doors[flag].door_y = i;
	info->doors[flag].is_open = 0;
	flag++;
	return (false);
}
