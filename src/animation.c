/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:01:43 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/15 16:49:44 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_time()
{
	struct timeval		tv;
	
	if (gettimeofday(&tv, NULL) == -1)
		exit(1);// in clean way
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_texture *update_tex(t_info *info)
{
	static int idx = 4;

	if (get_time() - info->last_time < 1)
		return (&info->mlx.tex[idx]);

	info->last_time = get_time(); // Update time for next interval
	idx++;
	if (idx > 9)
		idx = 5; // Wrap around to starting frame
	return (&info->mlx.tex[idx]);
}
