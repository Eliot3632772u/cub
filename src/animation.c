/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:01:43 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/15 14:28:14 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*update_tex(t_info *info)
{
	static int	frame;
	static int  idx = 4;

	if (frame != 60)
	{
		frame++;
		return (&info->mlx.tex[idx]);
	}
	frame = 0;
	idx++;
	if (idx > 9)
		idx = 5;
	return (&info->mlx.tex[idx]);
}
