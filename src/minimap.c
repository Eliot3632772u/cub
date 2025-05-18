/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:00:44 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/18 07:46:05 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	color(t_info *info, int map_x, int map_y)
{
	if (info->map[map_y][map_x] == '0')
		return (0xCCCCCC);
	else if (info->map[map_y][map_x] == '1')
		return (0x444444);
	else if (info->map[map_y][map_x] == '2')
		return (0x0000);
	return (0);
}

void	put_map_pix(t_info *info, int screen_x, int screen_y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < MINIMAP_TILE)
	{
		j = 0;
		while (j < MINIMAP_TILE)
		{
			my_mlx_pixel_put(&info->mlx, screen_x + j, screen_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_util(t_info *info, int player_map_x, \
	int player_map_y, int dy)
{
	int	dx;
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;

	dx = -MINIMAP_RADIUS;
	while (dx <= MINIMAP_RADIUS)
	{
		map_x = player_map_x + dx;
		map_y = player_map_y + dy;
		if (map_x < 0 || map_y < 0 || map_x >= info->map_w || \
			map_y >= info->map_h || info->map[map_y][map_x] == ' ')
		{
			dx++;
			continue ;
		}
		screen_x = (dx + MINIMAP_RADIUS) * MINIMAP_TILE;
		screen_y = (dy + MINIMAP_RADIUS) * MINIMAP_TILE;
		if (map_x == player_map_x && map_y == player_map_y)
			put_map_pix(info, screen_x, screen_y, 0xff0000);
		else
			put_map_pix(info, screen_x, screen_y, color(info, map_x, map_y));
		dx++;
	}
}

void	draw_minimap(t_info *info)
{
	int	player_map_x;
	int	player_map_y;
	int	dy;

	player_map_x = info->player.px / info->tile_size;
	player_map_y = info->player.py / info->tile_size;
	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		draw_minimap_util(info, player_map_x, player_map_y, dy);
		dy++;
	}
}
