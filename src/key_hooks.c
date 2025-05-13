/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:06:41 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/13 09:52:44 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int key_hook(void *inf)
{
	t_info	*info;
    
	info = inf;
	if (info->keys.key_forward)
		move_forward(info);
	else if (info->keys.key_back)
		move_back(info);
	else if (info->keys.key_left)
		move_left(info);
	else if (info->keys.key_right)
		move_right(info);
	else if (info->keys.key_rot_l)
		rotate_left(info);
	else if (info->keys.key_rot_r)
		rotate_right(info);
    return (0);
}

int press(int keycode, void *inf)
{
	t_info	*info;

	info = inf;
	if (keycode == UP)
		info->keys.key_forward = 1;
	else if (keycode == DOWN)
		info->keys.key_back = 1;
	else if (keycode == LEFT)
		info->keys.key_left = 1;
	else if (keycode == RIGHT)
		info->keys.key_right = 1;
	else if (keycode == ROT_L)
		info->keys.key_rot_l = 1;
	else if (keycode == ROT_R)
		info->keys.key_rot_r = 1;
	else if (keycode == DOOR_OPEN)
		open_door(info);
	else if (keycode == DOOR_CLOSE)
		close_door(info);
	else if (keycode == ESC)
		exit_prog(info);
	return (0);
}

int release(int keycode, void *inf)
{
	t_info	*info;

	info = inf;
	if (keycode == UP)
		info->keys.key_forward = 0;
	else if (keycode == DOWN)
		info->keys.key_back = 0;
	else if (keycode == LEFT)
		info->keys.key_left = 0;
	else if (keycode == RIGHT)
		info->keys.key_right = 0;
	else if (keycode == ROT_L)
		info->keys.key_rot_l = 0;
	else if (keycode == ROT_R)
		info->keys.key_rot_r = 0;
	return (0);
}
