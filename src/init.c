/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabhi <irabhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:49:28 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/10 15:21:08 by irabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int **maptr(void) {
    int i, j;
    static int raw_map[24][24] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,3,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,1,2,1,3,0,0,0,0,1,0,1,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int **worldMap = malloc(sizeof(int *) * 24);
    if (!worldMap)
        return NULL;

    for (i = 0; i < 24; i++) {
        worldMap[i] = malloc(sizeof(int) * 24);
        if (!worldMap[i]) {
            // Free previously allocated rows if allocation fails
            while (--i >= 0)
                free(worldMap[i]);
            free(worldMap);
            return NULL;
        }
        for (j = 0; j < 24; j++) {
            worldMap[i][j] = raw_map[i][j];
        }
    }

    return worldMap;
}

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
			// free_elemes(elems, "TEXTURES");
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
	info->mlx.tex[0].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_1.xpm" 
		, &info->mlx.tex[0].width, &info->mlx.tex[0].height);
	info->mlx.tex[1].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_2.xpm" 
		, &info->mlx.tex[1].width, &info->mlx.tex[1].height);
	info->mlx.tex[2].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_3.xpm" 
		, &info->mlx.tex[2].width, &info->mlx.tex[2].height);
	info->mlx.tex[3].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_4.xpm" 
		, &info->mlx.tex[3].width, &info->mlx.tex[3].height);
	info->mlx.tex[4].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/door_b.xpm" // door
		, &info->mlx.tex[4].width, &info->mlx.tex[4].height);
		
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

void	init_map_data(t_info *info)
{
    // t_elements  elems;

    // ft_memset(&elems, 0, sizeof(t_elements));
    // parse_file(&elems, file_name);
	info->mlx.cel_clr = 0xaaaa00; //elems.ceil_rgb;
    info->mlx.flr_clr =0x00aaaa; // elems.floor_rgb;
	info->map = maptr();
    
	info->doors[0].door_x = 8;
	info->doors[0].door_y = 8;   // init an array of t_door the size of number of doors and set x and y in the grid and the variable door.is_open to 0
	info->doors[0].is_open = 0;
	info->n_doors = 1;

    
	init_tex(info);
	info->player.angle = deg_to_rad(90); // get this value from map, N = 90, S = 270, E = 180, W = 0
	info->player.pX = 3 * info->TILE_SIZE;
    info->player.pY = 3 * info->TILE_SIZE;
}
