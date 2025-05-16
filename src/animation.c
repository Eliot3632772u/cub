/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:01:43 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/16 14:45:35 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	get_time()
{
	struct timeval		tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_texture *update_tex(t_info *info)
{
	static int idx = 4;

	if (get_time() - info->last_time < 300)
		return (&info->mlx.tex[idx]);

	info->last_time = get_time(); // Update time for next interval
	idx++;
	if (idx > 9)
		idx = 5; // Wrap around to starting frame
	return (&info->mlx.tex[idx]);
}
