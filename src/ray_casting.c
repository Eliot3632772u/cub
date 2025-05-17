/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:58:51 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/17 21:06:14 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall(t_info *info, int column)
{
	info->tmp.wall_h = calc_wall_height(info);
	render(info, column);
}

int	raycasting(void *inf)
{
	t_info	*info;
	int		rays;

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
	return (0);
}
