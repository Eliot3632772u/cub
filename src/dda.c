/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:47:39 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/16 18:01:01 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	store_wall_hit(t_info *info, int mapY, int mapX, int side)
{
	info->ray.map_x = mapX;
	info->ray.map_y = mapY;
	info->ray.side = side;
}

void	dist_to_wall(t_info *info, int side)
{
	if (side == 0)
	{
		info->player.dist_to_wall = \
		(info->player.side_x - info->player.dx) * info->tile_size;
		info->ray.hit_x = \
		info->player.py + info->player.dist_to_wall * sin(info->ray.angle);
	}
	else
	{
		info->player.dist_to_wall = \
		(info->player.side_y - info->player.dy) * info->tile_size;
		info->ray.hit_x = \
		info->player.px + info->player.dist_to_wall * cos(info->ray.angle);
	}
	info->player.dist_to_wall *= cos(info->ray.angle - info->player.angle);
}

void	tex_column(t_info *info, int side)
{
	int		tex_width;

	tex_width = 64;
	if (info->map[info->ray.map_y][info->ray.map_x] == '2')
		tex_width = info->mlx.tex[5].width;
	else if (side == 0)
	{
		if (info->ray.dx < 0)
			tex_width = info->mlx.tex[3].width;
		else
			tex_width = info->mlx.tex[2].width;
	}
	else if (side == 1)
	{
		if (info->ray.dy < 0)
			tex_width = info->mlx.tex[0].width;
		else
			tex_width = info->mlx.tex[1].width;
	}
	info->ray.hit_x = fmod(info->ray.hit_x, info->tile_size);
	info->ray.tex_x = \
	(int)(info->ray.hit_x / info->tile_size * tex_width);
}

void	dda(t_info *info, int mapX, int mapY)
{
	int		side;

	while (1)
	{
		if (info->player.side_x < info->player.side_y)
		{
			info->player.side_x += info->player.dx;
			mapX += info->player.step_x;
			side = 0;
		}
		else
		{
			info->player.side_y += info->player.dy;
			mapY += info->player.step_y;
			side = 1;
		}
		if (mapX < 0 || mapX >= info->map_w || mapY < 0 || \
			mapY >= info->map_h || info->map[mapY][mapX] != '0')
			break ;
	}
	store_wall_hit(info, mapY, mapX, side);
	dist_to_wall(info, side);
	tex_column(info, side);
}

void	distance_to_wall(t_info *info, int column)
{
	int	map_x;
	int	map_y;

	map_x = (int)(info->player.px / info->tile_size);
	map_y = (int)(info->player.py / info->tile_size);
	calc_ray_angle(info, column);
	calc_delta(info);
	ray_increment(info, map_x, map_y);
	dda(info, map_x, map_y);
}
