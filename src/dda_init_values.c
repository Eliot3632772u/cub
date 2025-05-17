/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_init_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:44:19 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/17 10:49:36 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	deg_to_rad(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	select_angle(t_info *info)
{
	if (info->map[info->p_y][info->p_x] == 'N')
		return (deg_to_rad(270));
	else if (info->map[info->p_y][info->p_x] == 'S')
		return (deg_to_rad(90));
	else if (info->map[info->p_y][info->p_x] == 'E')
		return (deg_to_rad(0));
	else
		return (deg_to_rad(180));
}

void	calc_ray_angle(t_info *info, int column)
{
	double	camera_x;

	camera_x = 2.0 * (double)column / (double)SCREENWIDTH - 1.0;
	info->ray.angle = \
	info->player.angle + atan(camera_x * tan(deg_to_rad(info->fov) / 2));
	info->ray.dx = cos(info->ray.angle);
	info->ray.dy = sin(info->ray.angle);
}

void	ray_increment(t_info *info, int map_x, int map_y)
{
	if (info->ray.dx < 0)
	{
		info->player.step_x = -1;
		info->player.side_x = (info->player.px - map_x * info->tile_size) \
		/ info->tile_size * info->player.dx;
	}
	else
	{
		info->player.step_x = 1;
		info->player.side_x = ((map_x + 1) * info->tile_size - info->player.px) \
		/ info->tile_size * info->player.dx;
	}
	if (info->ray.dy < 0)
	{
		info->player.step_y = -1;
		info->player.side_y = (info->player.py - map_y * info->tile_size) \
		/ info->tile_size * info->player.dy;
	}
	else
	{
		info->player.step_y = 1;
		info->player.side_y = ((map_y + 1) * info->tile_size - info->player.py) \
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
