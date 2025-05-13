/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:58:51 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/13 12:14:52 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall(t_info *info, int column)
{
	info->tmp.wall_h = calc_wall_height(info);
	render(info, column);
}

int raycasting(void *inf)
{
	t_info	*info;
	int	rays;

	rays = -1;
	info = inf;
	key_hook(inf);
	while (++rays < SCREENWIDTH)
	{
		distance_to_wall(info, rays);
		draw_wall(info, rays);
	}
	mlx_put_image_to_window(info->mlx.con, info->mlx.win, info->mlx.img, 0, 0);
	draw_minimap(info);
	draw_minimap_player(info);
	update_tex(info);
	return 0;
}
