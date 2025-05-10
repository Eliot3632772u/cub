#include "../includes/cub3d.h"


#define mapWidth 24
#define mapHeight 24


#include <stdlib.h>


void	init_info(t_info *info)
{
	init_mlx(info);
	init_vars(info);
	init_map_data(info);
}

int main()
{
  t_info info;

  init_info(&info);
  mlx_hook(info.mlx.win, 3, 1L<<1, release, &info);
  mlx_hook(info.mlx.win, 2, 1L<<0, press, &info);
  mlx_hook(info.mlx.win, 6, 1L<<6, mouse_move, &info);
  mlx_loop_hook(info.mlx.con, raycasting, &info);
  mlx_loop(info.mlx.con);
}