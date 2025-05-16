/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:53:05 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/16 18:07:27 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calc_wall_height(t_info *info)
{
	double	dist_to_proj_plan;
	double	wall_height;

	dist_to_proj_plan = (SCREENWIDTH / 2.0) / tan(deg_to_rad(info->fov / 2));
	wall_height = \
	(info->tile_size / info->player.dist_to_wall) * dist_to_proj_plan;
	return ((int)wall_height);
}
