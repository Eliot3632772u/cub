/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:08:00 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/11 12:55:15 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void open_door(t_info *info)
{
	int		px;
	int		py;
	int		i;

    px = (int)((info->player.pX + cos(info->player.angle) * 90)\
	 / info->TILE_SIZE);
    py = (int)((info->player.pY + sin(info->player.angle) * 90)\
	 / info->TILE_SIZE);
	if (info->map[py][px] == '2')
	{
		i = 0;
		while (i < info->n_doors)
		{
			if (info->doors[i].door_x == px && info->doors[i].door_y == py)
			{
				info->doors[i].is_open = 1;
				info->map[py][px] = '0';
				break;
			}
			i++;
		}
	}
}

void close_door(t_info *info)
{
	int		px;
	int		py;
	int		i;

	px = (int)((info->player.pX + cos(info->player.angle) * 90)\
	 / info->TILE_SIZE);
	py = (int)((info->player.pY + sin(info->player.angle) * 90)\
	 / info->TILE_SIZE);
	i = 0;
	while (i < info->n_doors)
	{
		if (info->doors[i].door_x == px && info->doors[i].door_y == py)
		{
			info->doors[i].is_open = 0;
			info->map[py][px] = '2';
			break;
		}
		i++;
	}
}
