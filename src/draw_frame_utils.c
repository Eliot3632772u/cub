/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:55:17 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/16 18:52:09 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_mlx *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_texture	*select_texture(t_info *info)
{
	if (info->ray.map_x > -1 && info->ray.map_y > -1 && \
		info->map[info->ray.map_y][info->ray.map_x] == '2')
	{
		info->ray.map_x = -1;
		info->ray.map_y = -1;
		return (update_tex(info));
	}
	if (info->ray.side == 0)
	{
		if (info->ray.dx < 0)
			return (&info->mlx.tex[2]);
		else
			return (&info->mlx.tex[3]);
	}
	else
	{
		if (info->ray.dy < 0)
			return (&info->mlx.tex[0]);
		else
			return (&info->mlx.tex[1]);
	}
}
