/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:03:36 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/17 08:33:18 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_info *info)
{
	double	dx;
	double	dy;

	dx = cos(info->player.angle);
	dy = sin(info->player.angle);
	if (check_inter(info, info->player.angle, 0))
		return ;
	info->player.px += dx * MOVE_SPEED;
	info->player.py += dy * MOVE_SPEED;
}

void	move_back(t_info *info)
{
	double	dx;
	double	dy;

	dx = cos(info->player.angle);
	dy = sin(info->player.angle);
	if (check_inter_back(info, info->player.angle, 0))
		return ;
	info->player.px -= dx * MOVE_SPEED;
	info->player.py -= dy * MOVE_SPEED;
}

void	move_left(t_info *info)
{
	double	angle;
	double	dx;
	double	dy;

	angle = info->player.angle - PI / 2;
	dx = cos(angle);
	dy = sin(angle);
	if (check_inter(info, angle, 0))
		return ;
	info->player.px += dx * MOVE_SPEED;
	info->player.py += dy * MOVE_SPEED;
}

void	move_right(t_info *info)
{
	double	angle;
	double	dx;
	double	dy;

	angle = info->player.angle + PI / 2;
	dx = cos(angle);
	dy = sin(angle);
	if (check_inter(info, angle, 0))
		return ;
	info->player.px += dx * MOVE_SPEED;
	info->player.py += dy * MOVE_SPEED;
}

int	mouse_move(int x, int y, void *inf)
{
	static int	last_x = -1;
	t_info		*info;
	int			delta_x;

	(void)y;
	info = inf;
	if (last_x == -1)
		last_x = x;
	delta_x = x - last_x;
	last_x = x;
	info->player.angle += delta_x * ROT_SPEED;
	if (info->player.angle < 0)
		info->player.angle += 2 * PI;
	else if (info->player.angle >= 2 * PI)
		info->player.angle -= 2 * PI;
	return (0);
}
