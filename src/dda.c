/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:47:39 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 09:47:55 by irabhi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	store_wall_hit(t_info *info,int mapY, int mapX, int side)
{
	if (mapY >= 0 && mapX >= 0)
	{
		info->ray.mapX = mapX;
		info->ray.mapY = mapY;
	}
	info->ray.side = side;
}

void	dist_to_wall(t_info *info, int side)
{
	if (side == 0)
	{
		info->player.dist_to_wall =\
		(info->player.sideX - info->player.dX) * info->TILE_SIZE;
		info->ray.hit_x =\
		info->player.pY + info->player.dist_to_wall * sin(info->ray.angle);
	}
	else
	{
		info->player.dist_to_wall =\
		(info->player.sideY - info->player.dY) * info->TILE_SIZE;
		info->ray.hit_x =\
		info->player.pX + info->player.dist_to_wall * cos(info->ray.angle);
	}
	info->player.dist_to_wall *= cos(info->ray.angle - info->player.angle);
}

void	tex_column(t_info *info, int side)
{
	info->ray.hit_x = fmod(info->ray.hit_x, info->TILE_SIZE);
	info->ray.tex_x =\
	(int)(info->ray.hit_x / info->TILE_SIZE * info->mlx.tex[0].width);
	if (side == 0 && info->ray.dX > 0)
		info->ray.tex_x = info->mlx.tex[0].width - info->ray.tex_x - 1;
	if (side == 1 && info->ray.dY < 0)
		info->ray.tex_x = info->mlx.tex[0].width - info->ray.tex_x - 1;
}

void	dda(t_info *info, int mapX, int mapY)
{
	int		side;

	while (1)
	{
		if (info->player.sideX < info->player.sideY)
		{
			info->player.sideX += info->player.dX;
			mapX += info->player.step_X;
			side = 0;
		}
		else
		{
			info->player.sideY += info->player.dY;
			mapY += info->player.step_Y;
			side = 1;
		}
		if (mapX < 0 || mapX >= info->map_w || mapY < 0 ||\
			mapY >= info->map_h || info->map[mapY][mapX] != 0)
			break;
	}
	store_wall_hit(info, mapY, mapX, side);
	dist_to_wall(info, side);
	tex_column(info, side);
}

void	distance_to_wall(t_info *info, int column)
{
	int		mapX;
	int		mapY;

	mapX = (int)(info->player.pX / info->TILE_SIZE);
	mapY = (int)(info->player.pY / info->TILE_SIZE);
	calc_ray_angle(info, column);
	calc_dist(info, mapX, mapY);
	calc_delta(info);
	ray_increment(info, mapX, mapY);
	dda(info, mapX, mapY);
}