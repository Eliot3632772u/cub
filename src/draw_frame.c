/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:51:25 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 14:50:20 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"




void	put_wall_util(t_info *info, double step, double tex_pos, int column)
{
	int		y;
	int		color;
	char	*pixel;
	int		tex_y;

	y = info->tmp.wall_start;
	while (y < info->tmp.wall_start + info->tmp.wall_h && y < screenHeight)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= 0 && tex_y < info->tmp.tex->height &&\
			 info->ray.tex_x >= 0 && info->ray.tex_x < info->tmp.tex->width)
		{
			pixel = info->tmp.tex->addr + tex_y * info->tmp.tex->line_len +\
			 info->ray.tex_x * (info->tmp.tex->bpp / 8);
			color = *(unsigned int *)pixel;
            my_mlx_pixel_put(&info->mlx, column, y, color);
		}
		tex_pos += step;
		y++;
	}
}

void	put_wall(t_info *info, int column)
{
	double	step;
	double	tex_pos;

	info->tmp.tex = select_texture(info);
	step = (double)info->tmp.tex->height / info->tmp.wall_h;
	tex_pos = (info->tmp.wall_start - screenHeight / 2 + info->tmp.wall_h / 2)\
	 * step;
	put_wall_util(info, step, tex_pos, column);
}


void	put_floor(t_info *info, int column)
{
	int	y;

	y = info->tmp.wall_end;
	while (y < screenHeight)
	{
		my_mlx_pixel_put(&info->mlx, column, y, info->mlx.flr_clr);
		y++;
	}
}

void	put_ceiling(t_info *info, int column)
{
	int		y;

	y = 0;
	while (y < info->tmp.wall_start)
	{
		my_mlx_pixel_put(&info->mlx, column, y, info->mlx.cel_clr);
		y++;
	}
}

void	render(t_info *info, int column)
{
	info->tmp.wall_start = (screenHeight / 2) - (info->tmp.wall_h / 2);
	info->tmp.wall_end = info->tmp.wall_start + info->tmp.wall_h;
	if (info->tmp.wall_start < 0)
		info->tmp.wall_start = 0;
	if (info->tmp.wall_end > screenHeight)
		info->tmp.wall_end = screenHeight;
	put_ceiling(info, column);
	put_wall(info, column);
	put_floor(info, column);
}
