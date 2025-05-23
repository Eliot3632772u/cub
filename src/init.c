/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:49:28 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/17 09:47:32 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_tex_util(t_info *info)
{
	int		i;

	i = -1;
	while (++i < 10)
	{
		if (info->mlx.tex[i].img == NULL)
		{
			free_textures(info);
			free_and_exit(info, NULL, "Invalid Textures");
		}
	}
	i = -1;
	while (++i < 10)
	{
		info->mlx.tex[i].addr = mlx_get_data_addr(info->mlx.tex[i].img, \
		&info->mlx.tex[i].bpp, &info->mlx.tex[i].line_len, \
		&info->mlx.tex[i].endian);
	}
}

void	init_tex(t_info *info)
{
	static int	i = -1;

	while (++i < 10)
		info->mlx.tex[i].img = NULL;
	info->mlx.tex[0].img = mlx_xpm_file_to_image(info->mlx.con, info->north \
		, &info->mlx.tex[0].width, &info->mlx.tex[0].height);
	info->mlx.tex[1].img = mlx_xpm_file_to_image(info->mlx.con, info->south \
		, &info->mlx.tex[1].width, &info->mlx.tex[1].height);
	info->mlx.tex[2].img = mlx_xpm_file_to_image(info->mlx.con, info->west \
		, &info->mlx.tex[2].width, &info->mlx.tex[2].height);
	info->mlx.tex[3].img = mlx_xpm_file_to_image(info->mlx.con, info->east \
		, &info->mlx.tex[3].width, &info->mlx.tex[3].height);
	info->mlx.tex[4].img = mlx_xpm_file_to_image(info->mlx.con, \
	"./tex/door_b.xpm", &info->mlx.tex[4].width, &info->mlx.tex[4].height);
	info->mlx.tex[5].img = mlx_xpm_file_to_image(info->mlx.con, \
	"./tex/anim0.xpm", &info->mlx.tex[5].width, &info->mlx.tex[5].height);
	info->mlx.tex[6].img = mlx_xpm_file_to_image(info->mlx.con, \
	"./tex/anim1.xpm", &info->mlx.tex[6].width, &info->mlx.tex[6].height);
	info->mlx.tex[7].img = mlx_xpm_file_to_image(info->mlx.con, \
	"./tex/anim2.xpm", &info->mlx.tex[7].width, &info->mlx.tex[7].height);
	info->mlx.tex[8].img = mlx_xpm_file_to_image(info->mlx.con, \
	"./tex/anim3.xpm", &info->mlx.tex[8].width, &info->mlx.tex[8].height);
	info->mlx.tex[9].img = mlx_xpm_file_to_image(info->mlx.con, \
	"./tex/anim4.xpm", &info->mlx.tex[9].width, &info->mlx.tex[9].height);
	init_tex_util(info);
}

void	init_mlx(t_info *info)
{
	info->mlx.con = NULL;
	info->mlx.win = NULL;
	info->mlx.img = NULL;
	info->mlx.con = mlx_init();
	if (info->mlx.con == NULL)
		exit (1);
	info->mlx.img = mlx_new_image(info->mlx.con, SCREENWIDTH, SCREENHIGHT);
	if (!info->mlx.img)
	{
		mlx_destroy_display(info->mlx.con);
		exit(1);
	}
	info->mlx.addr = mlx_get_data_addr(info->mlx.img, &info->mlx.bpp, \
	&info->mlx.line_len, &info->mlx.endian);
}

void	init_vars(t_info *info)
{
	info->ray.map_x = -1;
	info->ray.map_y = -1;
	info->keys.key_back = 0;
	info->keys.key_forward = 0;
	info->keys.key_left = 0;
	info->keys.key_right = 0;
	info->keys.key_rot_l = 0;
	info->keys.key_rot_r = 0;
	info->tile_size = 64;
	info->fov = 60;
}

void	init_map_data(t_info *info)
{
	struct timeval		tv;

	info->map_h = 0;
	info->map_w = 0;
	info->mlx.cel_clr = 0;
	info->mlx.flr_clr = 0;
	info->p_x = 0;
	info->p_y = 0;
	info->map = NULL;
	info->north = NULL;
	info->south = NULL;
	info->east = NULL;
	info->west = NULL;
	info->doors = NULL;
	info->n_doors = 0;
	parse_file(info);
	info->player.angle = select_angle(info);
	info->player.px = info->p_x * info->tile_size + 0.5 * info->tile_size;
	info->player.py = info->p_y * info->tile_size + 0.5 * info->tile_size;
	info->map[info->p_y][info->p_x] = '0';
	init_tex(info);
	gettimeofday(&tv, NULL);
	info->last_time = (tv.tv_sec * 1000) + (tv.tv_sec / 1000);
}
