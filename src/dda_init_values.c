/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_init_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:44:19 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 09:46:04 by irabhi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

double	deg_to_rad(double degrees) 
{
	return degrees * (PI / 180.0);
}

void	calc_ray_angle(t_info *info, int column)
{
	double	camera_x;

	camera_x = 2.0 * (double)column / (double)screenWidth - 1.0;
	info->ray.angle =\
	info->player.angle + atan(camera_x * tan(deg_to_rad(info->fov) / 2));
	info->ray.angle = fmod(info->ray.angle, 2 * PI);
	if (info->ray.angle < 0)
    	info->ray.angle += 2 * PI;
	info->ray.dX = cos(info->ray.angle);
	info->ray.dY = sin(info->ray.angle);
}

void	ray_increment(t_info *info, int mapX, int mapY)
{
	if (info->ray.dX < 0)
	{
		info->player.step_X = -1;
		info->player.sideX = (info->player.pX - mapX * info->TILE_SIZE)\
		/ info->TILE_SIZE * info->player.dX;
	}
	else
	{
		info->player.step_X = 1;
		info->player.sideX = ((mapX + 1) * info->TILE_SIZE - info->player.pX)\
		/ info->TILE_SIZE * info->player.dX;
	}
	if (info->ray.dY < 0)
	{
		info->player.step_Y = -1;
		info->player.sideY = (info->player.pY - mapY * info->TILE_SIZE)\
		/ info->TILE_SIZE * info->player.dY;
	}
	else
	{
		info->player.step_Y = 1;
		info->player.sideY = ((mapY + 1) * info->TILE_SIZE - info->player.pY)\
		/ info->TILE_SIZE * info->player.dY;
	}
}
void	calc_delta(t_info *info)
{
	if (info->ray.dX == 0)
    	info->player.dX = 1e30;
	else
		info->player.dX = fabs(1.0 / info->ray.dX);
	if (info->ray.dY == 0)
		info->player.dY = 1e30;
	else
		info->player.dY = fabs(1.0 / info->ray.dY);
}