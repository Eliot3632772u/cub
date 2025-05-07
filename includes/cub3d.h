#pragma once

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <math.h>

# define PI 3.14159265358979323846
# define MOVE_SPEED 3
# define ROT_SPEED 0.02
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ROT_L 65361
# define ROT_R 65363
# define MINIMAP_RADIUS 5
# define MINIMAP_TILE 10
# define screenWidth 1240
# define screenHeight 780

typedef struct  s_player{

    double      pX;
    double      pY;
    double      dX;
    double      dY;
    double      planeX;
    double      planeY;
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
    t_texture  tex[6];
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

}              t_tmp;

typedef struct s_keys{

    int        key_forward;
    int        key_back;
    int        key_left;
    int        key_right;
    int        key_rot_r;
    int        key_rot_l;
}              t_keys;

typedef struct s_info{

    int        TILE_SIZE;
    double     fov;
    t_tmp      tmp;
    int **     map;
    int        map_h;
    int        map_w;
    t_ray      ray;
    t_player   player;
    t_mlx      mlx;
    t_keys     keys;

}              t_info;


int key_hook(void *inf);

