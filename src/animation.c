/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:01:43 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/11 20:30:16 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void update_tex(t_info *info)
{
	static int	frame;
	t_texture	*tmp;
	int	i;

	if (frame != 60)
	{
		frame++;
		return ;
	}
	frame = 0;
	tmp = &info->mlx.tex[5];
	i = 5;
	while (i < 9)
	{
		info->mlx.tex[i] = info->mlx.tex[i + 1];
		i++;
	}
	info->mlx.tex[i] = *tmp;
}
