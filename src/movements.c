/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:03:36 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 10:05:43 by irabhi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void move_forward(t_info *info)
{
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	dx = cos(info->player.angle);
	dy = sin(info->player.angle);
	stepx = ((info->player.pX + dx * (MOVE_SPEED +20))  )/ info->TILE_SIZE;
	stepy = ((info->player.pY +dy * (MOVE_SPEED+ 20))  )/ info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX += dx * MOVE_SPEED;
	info->player.pY += dy * MOVE_SPEED;
}

void move_back(t_info *info)
{
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	dx = cos(info->player.angle);
	dy = sin(info->player.angle);
	stepx = ((info->player.pX- dx * (MOVE_SPEED + 20)) ) / info->TILE_SIZE;
	stepy = ((info->player.pY - dy * (MOVE_SPEED + 20)) ) / info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX -= dx * MOVE_SPEED;
	info->player.pY -= dy * MOVE_SPEED;
}

void move_left(t_info *info)
{
	double	angle;
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	angle = info->player.angle - PI / 2;
	dx = cos(angle);
	dy = sin(angle);
	stepx = ((info->player.pX + dx * (MOVE_SPEED + 20)) )/ info->TILE_SIZE;
	stepy = ((info->player.pY + dy * (MOVE_SPEED  + 20))  ) / info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX += dx * MOVE_SPEED;
	info->player.pY += dy * MOVE_SPEED;
}

void move_right(t_info *info)
{
	double	angle;
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	angle = info->player.angle + PI / 2;
	dx = cos(angle);
	dy = sin(angle);
	stepx = ((info->player.pX + dx * (MOVE_SPEED + 20))) / info->TILE_SIZE;
	stepy = ((info->player.pY + dy * (MOVE_SPEED + 20))) / info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX += dx * MOVE_SPEED;
	info->player.pY += dy * MOVE_SPEED;
}

int mouse_move(int x, int y, void *inf)
{
    static int	last_x = -1;
    t_info 		*info;
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
