/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:53:05 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 09:53:32 by irabhi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	calc_wall_height(t_info *info)
{
	int		dist_to_proj_plan;

	dist_to_proj_plan = (screenWidth / 2) / tan(deg_to_rad(info->fov) / 2);
	return ((info->TILE_SIZE / info->player.dist_to_wall) * dist_to_proj_plan);
}