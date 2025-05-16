/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:08:00 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/16 18:05:57 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	open_door(t_info *info)
{
	int		px;
	int		py;
	int		i;

	px = (int)((info->player.px + cos(info->player.angle) * 90) \
	/ info->tile_size);
	py = (int)((info->player.py + sin(info->player.angle) * 90) \
	/ info->tile_size);
	if (info->map[py][px] == '2')
	{
		i = 0;
		while (i < info->n_doors)
		{
			if (info->doors[i].door_x == px && info->doors[i].door_y == py)
			{
				info->doors[i].is_open = 1;
				info->map[py][px] = '0';
				break ;
			}
			i++;
		}
	}
}

void	close_door(t_info *info)
{
	int		px;
	int		py;
	int		i;

	px = (int)((info->player.px + cos(info->player.angle) * 90) \
	/ info->tile_size);
	py = (int)((info->player.py + sin(info->player.angle) * 90) \
	/ info->tile_size);
	i = 0;
	while (i < info->n_doors)
	{
		if (info->doors[i].door_x == px && info->doors[i].door_y == py)
		{
			info->doors[i].is_open = 0;
			info->map[py][px] = '2';
			break ;
		}
		i++;
	}
}
