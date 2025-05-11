#pragma once

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../src/libft/libft.h"

# define PI 3.14159265358979323846
# define MOVE_SPEED 3
# define ROT_SPEED 0.02
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ROT_L 65361
# define ROT_R 65363
# define DOOR_OPEN 101
# define DOOR_CLOSE 102
# define MINIMAP_RADIUS 5
# define MINIMAP_TILE 10
# define screenWidth 1240
# define screenHeight 780

# define GENERIC_ERR_MSG "Fatal Issue Occured"
# define MAP_ERR_MSG "Invalid Map"


typedef struct  s_player{

	double      pX;
	double      pY;
	double      dX;
	double      dY;
	double      step_X;
	double      step_Y;
	double      sideX;
	double      sideY;
	double      angle;
	double      dist_to_wall;

}               t_player;

typedef struct  s_texture{

	void    *img;
	char    *addr;
	int     line_len;
	int     bpp;
	int     endian;
	int     width;
	int     height;

}               t_texture;

typedef struct  s_mlx{

	void*       win;
	void*       con;
	void*       img;
	void    *addr;
	int     line_len;
	int     bpp;
	int     endian;
	t_texture  tex[10];
	int         cel_clr;
	int         flr_clr;

}               t_mlx;

typedef struct s_ray{

	double     angle;
	double     dX;
	double     dY;
	double     hit_x;
	int        tex_x;
	int        mapX;
	int        mapY;
	int        side;

}              t_ray;

typedef struct s_tmp{

	int        wall_h;
	int        wall_start;
	int        wall_end;
	t_texture  *tex;
	int        tex_y;
	int        tex_pos;
	int        color;
	int        open_door;
	int        door_y;
	int        door_x;

}              t_tmp;

typedef struct s_keys{

	int        key_forward;
	int        key_back;
	int        key_left;
	int        key_right;
	int        key_rot_r;
	int        key_rot_l;
}              t_keys;

typedef struct s_door{

	int        door_x;
	int        door_y;
	int        is_open;
}              t_door;

typedef struct s_info
{
	int        TILE_SIZE;
	double     fov;
	t_tmp      tmp;
	char        **map;
	int        map_h;
	int        map_w;
	int        n_doors;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*file_name;
	int			fd;
	size_t      p_x;
	size_t      p_y;
	t_door     *doors;
	t_ray      ray;
	t_player   player;
	t_mlx      mlx;
	t_keys     keys;
}              t_info;

void		update_tex(t_info *info);
double		deg_to_rad(double degrees);
void		calc_ray_angle(t_info *info, int column);
void		ray_increment(t_info *info, int mapX, int mapY);
void		calc_delta(t_info *info);
void		store_wall_hit(t_info *info,int mapY, int mapX, int side);
void		dist_to_wall(t_info *info, int side);
void		tex_column(t_info *info, int side);
void		dda(t_info *info, int mapX, int mapY);
void		distance_to_wall(t_info *info, int column);
void		open_door(t_info *info);
void		close_door(t_info *info);
void		my_mlx_pixel_put(t_mlx *img, int x, int y, int color);
t_texture	*select_texture(t_info *info);
void		put_wall_util(t_info *info, double step, double tex_pos, int column);
void		put_wall(t_info *info, int column);
void		put_floor(t_info *info, int column);
void		put_ceiling(t_info *info, int column);
void		render(t_info *info, int column);
int			key_hook(void *inf);
int			press(int keycode, void *inf);
int			release(int keycode, void *inf);
int			pick_color(t_info *info, int map_x, int map_y);
void		put_map_pix(t_info *info, int screen_x, int screen_y, int color);
void		draw_minimap_util(t_info *info, int player_map_x, int player_map_y, int dy);
void		draw_minimap(t_info *info);
void		draw_minimap_player(t_info *info);
void		move_forward(t_info *info);
void		move_back(t_info *info);
void		move_left(t_info *info);
void		move_right(t_info *info);
int			mouse_move(int x, int y, void *inf);
void		draw_wall(t_info *info, int column);
int			raycasting(void *inf);
void		rotate_left(t_info *info);
void		rotate_right(t_info *info);
int			calc_wall_height(t_info *info);
void		init_tex_util(t_info *info);
void		init_tex(t_info *info);
void		init_mlx(t_info *info);
void		init_vars(t_info *info);
void		init_map_data(t_info *info);

void		parse_file(t_info *info);
void		print_my_elems(t_info *info);
void		free_elems(t_info *info, char *error);