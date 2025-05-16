/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:37:46 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/16 18:19:32 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
