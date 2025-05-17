/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:33:30 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/17 08:33:45 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_inter(t_info *info, double angle, double offset_angle)
{
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;
	double	i;

	i = -3;
	while (i < 3)
	{
		offset_angle = angle + (i * 0.05);
		dx = cos(offset_angle);
		dy = sin(offset_angle);
		stepx = (info->player.px + dx * (MOVE_SPEED + 20)) / info->tile_size;
		stepy = (info->player.py + dy * (MOVE_SPEED + 20)) / info->tile_size;
		if (stepx < 0 || stepx >= info->map_w || stepy < 0 || \
		stepy >= info->map_h || info->map[stepy][stepx] != '0')
			return (1);
		i += 0.2;
	}
	return (0);
}

int	check_inter_back(t_info *info, double angle, double offset_angle)
{
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;
	double	i;

	i = -3;
	while (i < 3)
	{
		offset_angle = angle + (i * 0.05);
		dx = cos(offset_angle);
		dy = sin(offset_angle);
		stepx = (info->player.px - dx * (MOVE_SPEED + 20)) / info->tile_size;
		stepy = (info->player.py - dy * (MOVE_SPEED + 20)) / info->tile_size;
		if (stepx < 0 || stepx >= info->map_w || stepy < 0 || \
		stepy >= info->map_h || info->map[stepy][stepx] != '0')
			return (1);
		i += 0.2;
	}
	return (0);
}
