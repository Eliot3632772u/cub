/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:00:44 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/13 12:12:45 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	pick_color(t_info *info, int map_x, int map_y)
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

void	draw_minimap_util(t_info *info, int player_map_x, int player_map_y, int dy)
{
	int		dx;
	int		map_x;
	int		map_y;
	int		screen_x;
	int		screen_y;

	dx = -MINIMAP_RADIUS;
	while (dx <= MINIMAP_RADIUS)
	{
		map_x = player_map_x + dx;
		map_y = player_map_y + dy;
		if (map_x < 0 || map_y < 0 || map_x >= info->map_w ||\
			map_y >= info->map_h || info->map[map_y][map_x] == ' ')
		{
			dx++;
			continue;
		}
		screen_x = (dx + MINIMAP_RADIUS) * MINIMAP_TILE;
		screen_y = (dy + MINIMAP_RADIUS) * MINIMAP_TILE;
		put_map_pix(info, screen_x, screen_y, pick_color(info, map_x, map_y));
		dx++;
	}
}

void	draw_minimap(t_info *info)
{
    int		player_map_x;
    int		player_map_y;
	int		dy;

	player_map_x = info->player.px / info->tile_size;
	player_map_y = info->player.py / info->tile_size;
	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		draw_minimap_util(info, player_map_x, player_map_y, dy);
		dy++;
	}
}

void	draw_minimap_player(t_info *info)
{
    int		center_x;
    int		center_y;
	int		i;
	int		j;

	center_x = MINIMAP_RADIUS * MINIMAP_TILE;
	center_y = MINIMAP_RADIUS * MINIMAP_TILE;
	i = -3;
	while (++i <=2)
	{
		j = -3;
		while (++j <= 2)
			my_mlx_pixel_put(&info->mlx, center_x + j, center_y + i, 0xFF0000);
	}
}
