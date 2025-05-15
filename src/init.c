/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:49:28 by irabhi            #+#    #+#             */
/*   Updated: 2025/05/15 11:31:52 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_info *info)
{
	int	i;

	i = -1;
	printf("SIZE of t_tex: %zu\n", sizeof(t_texture));
	while (++i < 10)
	{
		if (info->mlx.tex[i].img)
		{
			printf("%i %p\n", i, info->mlx.tex[i].img);
			mlx_destroy_image(info->mlx.con, info->mlx.tex[i].img);
		}
	}
}

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
		info->mlx.tex[i].addr = mlx_get_data_addr(info->mlx.tex[i].img,\
		&info->mlx.tex[i].bpp, &info->mlx.tex[i].line_len,\
		&info->mlx.tex[i].endian);
	}
}

void	set_tex(t_info *info)
{
	info->mlx.tex[0].img = NULL;
	info->mlx.tex[1].img = NULL;
	info->mlx.tex[2].img = NULL;
	info->mlx.tex[3].img = NULL;
	info->mlx.tex[4].img = NULL;
	info->mlx.tex[5].img = NULL;
	info->mlx.tex[6].img = NULL;
	info->mlx.tex[7].img = NULL;
	info->mlx.tex[8].img = NULL;
	info->mlx.tex[9].img = NULL;
}

void	init_tex(t_info *info)
{
	// ft_memset(&info->mlx.tex, 0, sizeof(t_texture) * 10);
	set_tex(info);
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
	info->mlx.win = mlx_new_window(info->mlx.con, SCREENWIDTH, SCREENHIGHT, "cube");
	if (info->mlx.win == NULL)
	{
		mlx_destroy_display(info->mlx.con);
		exit(1);
	}
	info->mlx.img = mlx_new_image(info->mlx.con, SCREENWIDTH, SCREENHIGHT);
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
	// print_my_elems(info);
}


// 106102872080800
// 106102872080928
// 106102872081056
// 106102872081184
// 106102872081312
// 106102872081568
// 106102872081696
// 106102872081824
// 106102872081952
// 106102872081568