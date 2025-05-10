/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:04:32 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 10:05:03 by irabhi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void rotate_left(t_info *info)
{
	info->player.angle -= ROT_SPEED;
	if (info->player.angle < 0)
		info->player.angle += 2 * PI;
}

void rotate_right(t_info *info)
{
	info->player.angle += ROT_SPEED;
	if (info->player.angle >= 2 * PI)
		info->player.angle -= 2 * PI;
}
