/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:49:28 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 11:11:11 by irabhi           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	init_tex_util(t_info *info, t_elements *elems)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		if (info->mlx.tex[i].img == NULL)
		{
			mlx_destroy_window(info->mlx.con, info->mlx.win);
			mlx_destroy_display(info->mlx.con);
			free_elemes(elems, "TEXTURES");
		}
	}
	i = -1;
	while (++i < 5)
	{
		info->mlx.tex[i].addr = mlx_get_data_addr(info->mlx.tex[i].img,\
		&info->mlx.tex[i].bpp, &info->mlx.tex[i].line_len,\
		&info->mlx.tex[i].endian);
	}
}

void	init_tex(t_info *info, t_elements *elems)
{
	info->mlx.tex[0].img = mlx_xpm_file_to_image(info->mlx.con, elems->west_file
		, &info->mlx.tex[0].width, &info->mlx.tex[0].height);
	info->mlx.tex[1].img = mlx_xpm_file_to_image(info->mlx.con, elems->east_file
		, &info->mlx.tex[1].width, &info->mlx.tex[1].height);
	info->mlx.tex[2].img = mlx_xpm_file_to_image(info->mlx.con, elems->north_file
		, &info->mlx.tex[2].width, &info->mlx.tex[2].height);
	info->mlx.tex[3].img = mlx_xpm_file_to_image(info->mlx.con, elems->south_file
		, &info->mlx.tex[3].width, &info->mlx.tex[3].height);
	info->mlx.tex[4].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/door_b.xpm" // door
		, &info->mlx.tex[4].width, &info->mlx.tex[4].height);
	init_tex_util(info, elems);
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
	info->map_h = 24;
	info->map_w = 24;
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

void	init_map_data(t_info *info, char *file_name)
{
    t_elements  elems;

    ft_memset(&elems, 0, sizeof(t_elements));
    parse_file(&elems, file_name);
	info->mlx.cel_clr = elems.ceil_rgb;
    info->mlx.flr_clr = elems.floor_rgb;
	info->map = elems.map;
    
	// info->doors[0].door_x = 8;
	// info->doors[0].door_y = 8;   // init an array of t_door the size of number of doors and set x and y in the grid and the variable door.is_open to 0
	// info->doors[0].is_open = 0;
	// info->n_doors = 1;

    
	init_tex(info, &elems);
	info->player.angle = deg_to_rad(90); // get this value from map, N = 90, S = 270, E = 180, W = 0
	info->player.pX = elems.player_col * info->TILE_SIZE;
    info->player.pY = elems.player_row * info->TILE_SIZE;
}
