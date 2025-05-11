/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:49:28 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/11 13:05:57 by irabhi           ###   ########.fr       */
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
			mlx_destroy_window(info->mlx.con, info->mlx.win);
			mlx_destroy_display(info->mlx.con);
			free_elems(info, "TEXTURES");
		}
	}
	i = -1;
	while (++i < 10)
	{
		info->mlx.tex[i].addr = mlx_get_data_addr(info->mlx.tex[i].img,\
		&info->mlx.tex[i].bpp, &info->mlx.tex[i].line_len,\
		&info->mlx.tex[i].endian);
	}
}

void	init_tex(t_info *info)
{
	info->mlx.tex[0].img = mlx_xpm_file_to_image(info->mlx.con, info->north 
		, &info->mlx.tex[0].width, &info->mlx.tex[0].height);
	info->mlx.tex[1].img = mlx_xpm_file_to_image(info->mlx.con, info->south 
		, &info->mlx.tex[1].width, &info->mlx.tex[1].height);
	info->mlx.tex[2].img = mlx_xpm_file_to_image(info->mlx.con, info->west 
		, &info->mlx.tex[2].width, &info->mlx.tex[2].height);
	info->mlx.tex[3].img = mlx_xpm_file_to_image(info->mlx.con, info->east 
		, &info->mlx.tex[3].width, &info->mlx.tex[3].height);
	info->mlx.tex[4].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/door_b.xpm"
		, &info->mlx.tex[4].width, &info->mlx.tex[4].height);
	printf("%s\n", info->north);
		
	info->mlx.tex[5].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/respawn_anchor_side0.xpm" 
		, &info->mlx.tex[5].width, &info->mlx.tex[5].height);
	info->mlx.tex[6].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/respawn_anchor_side1.xpm" 
		, &info->mlx.tex[6].width, &info->mlx.tex[6].height);
	info->mlx.tex[7].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/respawn_anchor_side2.xpm" 
		, &info->mlx.tex[7].width, &info->mlx.tex[7].height);
	info->mlx.tex[8].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/respawn_anchor_side3.xpm" 
		, &info->mlx.tex[8].width, &info->mlx.tex[8].height);
	info->mlx.tex[9].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/respawn_anchor_side4.xpm"
		, &info->mlx.tex[9].width, &info->mlx.tex[9].height);
	init_tex_util(info);
}

void	init_mlx(t_info *info)
{
	info->mlx.con = mlx_init();
	if (info->mlx.con == NULL)
		exit (1);
	info->mlx.win = mlx_new_window(info->mlx.con, screenWidth, screenHeight, "cube");
	if (info->mlx.win == NULL)
	{
		mlx_destroy_display(info->mlx.con);
		exit(1);
	}
	info->mlx.img = mlx_new_image(info->mlx.con, screenWidth, screenHeight);
	if (!info->mlx.img)
	{
		mlx_destroy_window(info->mlx.con, info->mlx.win);
		mlx_destroy_display(info->mlx.con);
		exit(1);
	}
	info->mlx.addr = mlx_get_data_addr(info->mlx.img, &info->mlx.bpp, &info->mlx.line_len, &info->mlx.endian);
}

void	init_vars(t_info *info)
{
	info->ray.mapX = -1;
	info->ray.mapY = -1;
	info->keys.key_back = 0;
	info->keys.key_forward = 0;
	info->keys.key_left = 0;
	info->keys.key_right = 0;
	info->keys.key_rot_l = 0;
	info->keys.key_rot_r = 0;
	info->TILE_SIZE = 64;
	info->fov = 60;
}

double	select_angle(t_info *info)
{
	if (info->map[info->p_y][info->p_x] == 'N')
		return(deg_to_rad(270));
	else if (info->map[info->p_y][info->p_x] == 'S')
		return(deg_to_rad(90));
	else if (info->map[info->p_y][info->p_x] == 'E')
		return(deg_to_rad(0));
	else
		return(deg_to_rad(180));
}

void	init_map_data(t_info *info)
{
	info->map_h = 0;
	info->map_w = 0;
	info->mlx.cel_clr = 0;
    info->mlx.flr_clr = 0;
	info->map = NULL;
	info->north = NULL;
	info->south = NULL;
	info->east = NULL;
	info->west = NULL;
	info->doors = NULL;
	info->n_doors = 0;
    parse_file(info);
	info->player.angle = select_angle(info);
	info->player.pX = info->p_x * info->TILE_SIZE;
    info->player.pY = info->p_y * info->TILE_SIZE;
	info->map[info->p_y][info->p_x] = '0';
	init_tex(info);
	print_my_elems(info);
}
