/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_init_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:44:19 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/13 12:07:14 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	deg_to_rad(double degrees) 
{
	return degrees * (PI / 180.0);
}

void	calc_ray_angle(t_info *info, int column)
{
	double	camera_x;

	camera_x = 2.0 * (double)column / (double)SCREENWIDTH - 1.0;
	info->ray.angle =\
	info->player.angle + atan(camera_x * tan(deg_to_rad(info->fov) / 2));
	info->ray.angle = fmod(info->ray.angle, 2 * PI);
	if (info->ray.angle < 0)
    	info->ray.angle += 2 * PI;
	info->ray.dx = cos(info->ray.angle);
	info->ray.dy = sin(info->ray.angle);
}

void	ray_increment(t_info *info, int mapX, int mapY)
{
	if (info->ray.dx < 0)
	{
		info->player.step_x = -1;
		info->player.side_x = (info->player.px - mapX * info->tile_size)\
		/ info->tile_size * info->player.dx;
	}
	else
	{
		info->player.step_x = 1;
		info->player.side_x = ((mapX + 1) * info->tile_size - info->player.px)\
		/ info->tile_size * info->player.dx;
	}
	if (info->ray.dy < 0)
	{
		info->player.step_y = -1;
		info->player.side_y = (info->player.py - mapY * info->tile_size)\
		/ info->tile_size * info->player.dy;
	}
	else
	{
		info->player.step_y = 1;
		info->player.side_y = ((mapY + 1) * info->tile_size - info->player.py)\
		/ info->tile_size * info->player.dy;
	}
}
void	calc_delta(t_info *info)
{
	if (info->ray.dx == 0)
    	info->player.dx = 1e30;
	else
		info->player.dx = fabs(1.0 / info->ray.dx);
	if (info->ray.dy == 0)
		info->player.dy = 1e30;
	else
		info->player.dy = fabs(1.0 / info->ray.dy);
}