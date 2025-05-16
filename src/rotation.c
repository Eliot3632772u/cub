/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:04:32 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/16 18:08:25 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_info *info)
{
	info->player.angle -= ROT_SPEED;
	if (info->player.angle < 0)
		info->player.angle += 2 * PI;
}

void	rotate_right(t_info *info)
{
	info->player.angle += ROT_SPEED;
	if (info->player.angle >= 2 * PI)
		info->player.angle -= 2 * PI;
}
