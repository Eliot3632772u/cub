/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:55:17 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 09:57:15 by irabhi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_mlx *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_texture	*select_texture(t_info *info)
{
	if (info->ray.mapX > -1 && info->ray.mapY > -1 &&\
		 info->map[info->ray.mapY][info->ray.mapX] == 2)
	{
		info->ray.mapX = -1;
		info->ray.mapY = -1;
		return (&info->mlx.tex[4]);
	}
	if (info->ray.side == 0)
	{
		if (info->ray.dX < 0)
			return (&info->mlx.tex[0]); // tex[0] in west texture
		else
			return (&info->mlx.tex[1]); // tex[1] is east texture
	}
	else
	{
		if (info->ray.dY < 0)
			return (&info->mlx.tex[2]);// tex[2] is north texture	
		else
			return (&info->mlx.tex[3]); // tex[3] is south texture
	}
}