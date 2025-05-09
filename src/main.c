#include "../includes/cub3d.h"


#define mapWidth 24
#define mapHeight 24


#include <stdlib.h>

int **maptr(void) {
    int i, j;
    static int raw_map[24][24] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
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


double	deg_to_rad(double degrees) 
{
	return degrees * (PI / 180.0);
}

void	calc_ray_angle(t_info *info, int column)
{
	double	camera_x;

	camera_x = 2.0 * (double)column / (double)screenWidth - 1.0;
	info->ray.angle =\
	info->player.angle + atan(camera_x * tan(deg_to_rad(info->fov) / 2));
	info->ray.angle = fmod(info->ray.angle, 2 * PI);
	if (info->ray.angle < 0)
    	info->ray.angle += 2 * PI;
	info->ray.dX = cos(info->ray.angle);
	info->ray.dY = sin(info->ray.angle);
}

void	ray_increment(t_info *info, int mapX, int mapY)
{
	if (info->ray.dX < 0)
	{
		info->player.step_X = -1;
		info->player.sideX = (info->player.pX - mapX * info->TILE_SIZE)\
		/ info->TILE_SIZE * info->player.dX;
	}
	else
	{
		info->player.step_X = 1;
		info->player.sideX = ((mapX + 1) * info->TILE_SIZE - info->player.pX)\
		/ info->TILE_SIZE * info->player.dX;
	}
	if (info->ray.dY < 0)
	{
		info->player.step_Y = -1;
		info->player.sideY = (info->player.pY - mapY * info->TILE_SIZE)\
		/ info->TILE_SIZE * info->player.dY;
	}
	else
	{
		info->player.step_Y = 1;
		info->player.sideY = ((mapY + 1) * info->TILE_SIZE - info->player.pY)\
		/ info->TILE_SIZE * info->player.dY;
	}
}
void	calc_delta(t_info *info)
{
	if (info->ray.dX == 0)
    	info->player.dX = 1e30;
	else
		info->player.dX = fabs(1.0 / info->ray.dX);
	if (info->ray.dY == 0)
		info->player.dY = 1e30;
	else
		info->player.dY = fabs(1.0 / info->ray.dY);
}

void	store_wall_hit(t_info *info,int mapY, int mapX, int side)
{
	if (mapY >= 0 && mapX >= 0)
	{
		info->ray.mapX = mapX;
		info->ray.mapY = mapY;
	}
	info->ray.side = side;
}

void	dist_to_wall(t_info *info, int side)
{
	if (side == 0)
	{
		info->player.dist_to_wall =\
		(info->player.sideX - info->player.dX) * info->TILE_SIZE;
		info->ray.hit_x =\
		info->player.pY + info->player.dist_to_wall * sin(info->ray.angle);
	}
	else
	{
		info->player.dist_to_wall =\
		(info->player.sideY - info->player.dY) * info->TILE_SIZE;
		info->ray.hit_x =\
		info->player.pX + info->player.dist_to_wall * cos(info->ray.angle);
	}
	info->player.dist_to_wall *= cos(info->ray.angle - info->player.angle);
}

void	tex_column(t_info *info, int side)
{
	info->ray.hit_x = fmod(info->ray.hit_x, info->TILE_SIZE);
	info->ray.tex_x =\
	(int)(info->ray.hit_x / info->TILE_SIZE * info->mlx.tex[0].width);
	if (side == 0 && info->ray.dX > 0)
		info->ray.tex_x = info->mlx.tex[0].width - info->ray.tex_x - 1;
	if (side == 1 && info->ray.dY < 0)
		info->ray.tex_x = info->mlx.tex[0].width - info->ray.tex_x - 1;
}

void	dda(t_info *info, int mapX, int mapY)
{
	int		side;

	while (1)
	{
		if (info->player.sideX < info->player.sideY)
		{
			info->player.sideX += info->player.dX;
			mapX += info->player.step_X;
			side = 0;
		}
		else
		{
			info->player.sideY += info->player.dY;
			mapY += info->player.step_Y;
			side = 1;
		}
		if (mapX < 0 || mapX >= info->map_w || mapY < 0 ||\
			mapY >= info->map_h || info->map[mapY][mapX] != 0)
			break;
	}
	store_wall_hit(info, mapY, mapX, side);
	dist_to_wall(info, side);
	tex_column(info, side);
}

void	distance_to_wall(t_info *info, int column)
{
	int		mapX;
	int		mapY;

	mapX = (int)(info->player.pX / info->TILE_SIZE);
	mapY = (int)(info->player.pY / info->TILE_SIZE);
	calc_ray_angle(info, column);
	calc_dist(info, mapX, mapY);
	calc_delta(info);
	ray_increment(info, mapX, mapY);
	dda(info, mapX, mapY);
}

int	calc_wall_height(t_info *info)
{
	int		dist_to_proj_plan;

	dist_to_proj_plan = (screenWidth / 2) / tan(deg_to_rad(info->fov) / 2);
	return ((info->TILE_SIZE / info->player.dist_to_wall) * dist_to_proj_plan);
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

void	my_mlx_pixel_put(t_mlx *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_wall_util(t_info *info, double step, double tex_pos, int column)
{
	int		y;
	int		color;
	char	*pixel;
	int		tex_y;

	y = info->tmp.wall_start;
	while (y < info->tmp.wall_start + info->tmp.wall_end && y < screenHeight)
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

void	draw_wall(t_info *info, int column)
{
	info->tmp.wall_h = calc_wall_height(info);
	render(info, column);
}

int	pick_color(t_info *info, int map_x, int map_y)
{
	if (info->map[map_y][map_x] == 0)
		return (0xCCCCCC);
	else if (info->map[map_y][map_x] == 1 || info->map[map_y][map_x] == 3)
		return (0x444444);
	else if (info->map[map_y][map_x] == 2)
		return (0x0000);
	return (0);
}

void	put_map_pix(t_info *info, int screen_x, int screen_y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < MINIMAP_TILE)
	{
		j = 0;
		while (j < MINIMAP_TILE)
		{
			my_mlx_pixel_put(&info->mlx, screen_x + j, screen_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_util(t_info *info, int player_map_x, int player_map_y, int dy)
{
	int		dx;
	int		map_x;
	int		map_y;
	int		screen_x;
	int		screen_y;

	dx = -MINIMAP_RADIUS;
	while (dx <= MINIMAP_RADIUS)
	{
		map_x = player_map_x + dx;
		map_y = player_map_y + dy;
		if (map_x < 0 || map_y < 0 || map_x >= info->map_w || map_y >= info->map_h)
		{
			dx++;
			continue;
		}
		screen_x = (dx + MINIMAP_RADIUS) * MINIMAP_TILE;
		screen_y = (dy + MINIMAP_RADIUS) * MINIMAP_TILE;
		put_map_pix(info, screen_x, screen_y, pick_color(info, map_x, map_y));
		dx++;
	}
}

void	draw_minimap(t_info *info)
{
    int		player_map_x;
    int		player_map_y;
	int		dy;

	player_map_x = info->player.pX / info->TILE_SIZE;
	player_map_y = info->player.pY / info->TILE_SIZE;
	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		draw_minimap_util(info, player_map_x, player_map_y, dy);
		dy++;
	}
}

void	draw_minimap_player(t_info *info)
{
    int		center_x;
    int		center_y;
	int		i;
	int		j;

	center_x = MINIMAP_RADIUS * MINIMAP_TILE;
	center_y = MINIMAP_RADIUS * MINIMAP_TILE;
	i = -3;
	while (++i <=2)
	{
		j = -3;
		while (++j <= 2)
			my_mlx_pixel_put(&info->mlx, center_x + j, center_y + i, 0xFF0000);
	}
}

void update_tex(t_info *info)
{
	static int	frame;
	t_texture	*tmp;
	int	i;

	if (frame != 60)
	{
		frame++;
		return ;
	}
	frame = 0;
	tmp = &info->mlx.tex[0];
	i = 0;
	while (i < 3)
	{
		info->mlx.tex[i] = info->mlx.tex[i + 1];
		i++;
	}
	info->mlx.tex[i] = *tmp;
}

int raycasting(void *inf)
{
	t_info	*info;
	int	rays;

	rays = -1;
	info = inf;
	key_hook(inf);
	while (++rays < screenWidth)
	{
		distance_to_wall(info, rays);
		draw_wall(info, rays);
	}
	mlx_put_image_to_window(info->mlx.con, info->mlx.win, info->mlx.img, 0, 0);
	draw_minimap(info);
	draw_minimap_player(info);
	update_tex(info);
	return 0;
}

void init_tex(t_info *info)
{
  int i;
  // load textures in this array info->mlx.tex, tex[0] is west , tex[1] is east, tex[2] is north, tex[3] is south


                                                            // only change the file name keep rest as it is
  info->mlx.tex[0].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_1.xpm", &info->mlx.tex[0].width, &info->mlx.tex[0].height);
  info->mlx.tex[1].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_2.xpm", &info->mlx.tex[1].width, &info->mlx.tex[1].height);
  info->mlx.tex[2].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_3.xpm", &info->mlx.tex[2].width, &info->mlx.tex[2].height);
  info->mlx.tex[3].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/wall_4.xpm", &info->mlx.tex[3].width, &info->mlx.tex[3].height);
  info->mlx.tex[4].img = mlx_xpm_file_to_image(info->mlx.con, "./textures/door_b.xpm", &info->mlx.tex[4].width, &info->mlx.tex[4].height);
  i = -1;
  while (++i < 5)
  {
    if (info->mlx.tex[i].img == NULL)
      exit(200);
  }
  i = -1;
  while (++i < 5)
  {
    info->mlx.tex[i].addr = mlx_get_data_addr(info->mlx.tex[i].img, \
      &info->mlx.tex[i].bpp, &info->mlx.tex[i].line_len, &info->mlx.tex[i].endian);
  }
}

void init_info(t_info *info)
{
  info->mlx.con = mlx_init(); // for mlx connection !!keep this as it is
  if (info->mlx.con == NULL)
    exit (1);
  info->mlx.win = mlx_new_window(info->mlx.con, screenWidth, screenHeight, "cube"); // for mlx window !!keep this as it is
  if (info->mlx.win == NULL)
    exit (10);
  info->mlx.img = mlx_new_image(info->mlx.con, screenWidth, screenHeight); // for the rendered image !!keep this as it is
  if (!info->mlx.img)
    exit (100);
  info->mlx.addr = mlx_get_data_addr(info->mlx.img, &info->mlx.bpp, &info->mlx.line_len, &info->mlx.endian); // !!keep this as it is
  info->mlx.cel_clr = 0x00AA00;// for the celeing color , init this one in parsing
  info->mlx.flr_clr = 0xAFAFf0;// for the floor color , init in parsing
  info->map = maptr();// the map array in ints , init in parsing
  info->map_h = 24;// map height
  info->map_w = 24;// map width
  info->ray.mapX = -1;
  info->ray.mapY = -1;
  info->keys.key_back = 0;// !!keep this as it is
  info->keys.key_forward = 0;// !!keep this as it is
  info->keys.key_left = 0;//!!keep this as it is
  info->keys.key_right = 0;//!!keep this as it is
  info->keys.key_rot_l = 0;//!!keep this as it is
  info->keys.key_rot_r = 0;//!!keep this as it is
  info->TILE_SIZE = 64;//!!keep this as it is
  info->fov = 60;//!!keep this as it is
  info->doors[0].door_x = 8;
  info->doors[0].door_y = 8;
  info->doors[0].is_open = 0;
  info->n_doors = 1;
  init_tex(info);
  info->player.angle = deg_to_rad(90); // this is the player angle extract from map : N = 90, S = 260, W = 0, E = 180; init in parsing
  info->player.pX = 250;// this player x position in map , if x = 4; then player.pX = 4 * info->TILE_SIZE, same for player y position init in parsing
  info->player.pY = 100;
}

void move_forward(t_info *info)
{
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	dx = cos(info->player.angle);
	dy = sin(info->player.angle);
	stepx = ((info->player.pX + dx * (MOVE_SPEED +20))  )/ info->TILE_SIZE;
	stepy = ((info->player.pY +dy * (MOVE_SPEED+ 20))  )/ info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX += dx * MOVE_SPEED;
	info->player.pY += dy * MOVE_SPEED;
}

void move_back(t_info *info)
{
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	dx = cos(info->player.angle);
	dy = sin(info->player.angle);
	stepx = ((info->player.pX- dx * (MOVE_SPEED + 20)) ) / info->TILE_SIZE;
	stepy = ((info->player.pY - dy * (MOVE_SPEED + 20)) ) / info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX -= dx * MOVE_SPEED;
	info->player.pY -= dy * MOVE_SPEED;
}

void move_left(t_info *info)
{
	double	angle;
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	angle = info->player.angle - PI / 2;
	dx = cos(angle);
	dy = sin(angle);
	stepx = ((info->player.pX + dx * (MOVE_SPEED + 20)) )/ info->TILE_SIZE;
	stepy = ((info->player.pY + dy * (MOVE_SPEED  + 20))  ) / info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX += dx * MOVE_SPEED;
	info->player.pY += dy * MOVE_SPEED;
}

void move_right(t_info *info)
{
	double	angle;
	double	dx;
	double	dy;
	int		stepx;
	int		stepy;

	angle = info->player.angle + PI / 2;
	dx = cos(angle);
	dy = sin(angle);
	stepx = ((info->player.pX + dx * (MOVE_SPEED + 20))) / info->TILE_SIZE;
	stepy = ((info->player.pY + dy * (MOVE_SPEED + 20))) / info->TILE_SIZE;
	if (info->map[stepy][stepx] != 0)
		return ;
	info->player.pX += dx * MOVE_SPEED;
	info->player.pY += dy * MOVE_SPEED;
}

void rotate_left(t_info *info)
{
	info->player.angle -= ROT_SPEED;
	if (info->player.angle < 0)
		info->player.angle += 2 * PI;
}

void rotate_right(t_info *info)
{
	info->player.angle += ROT_SPEED;
	if (info->player.angle >= 2 * PI)
		info->player.angle -= 2 * PI;
}
int key_hook(void *inf)
{
	t_info	*info;
    
	info = inf;
	if (info->keys.key_forward)
		move_forward(info);
	else if (info->keys.key_back)
		move_back(info);
	else if (info->keys.key_left)
		move_left(info);
	else if (info->keys.key_right)
		move_right(info);
	else if (info->keys.key_rot_l)
		rotate_left(info);
	else if (info->keys.key_rot_r)
		rotate_right(info);
    return (0);
}

void open_door(t_info *info)
{
	int		px;
	int		py;
	int		i;

    px = (int)((info->player.pX + cos(info->player.angle) * 90)\
	 / info->TILE_SIZE);
    py = (int)((info->player.pY + sin(info->player.angle) * 90)\
	 / info->TILE_SIZE);
	if (info->map[py][px] == 2)
	{
		i = 0;
		while (i < info->n_doors)
		{
			if (info->doors[i].door_x == px && info->doors[i].door_y == py)
			{
				info->doors[i].is_open = 1;
				info->map[py][px] = 0;
				break;
			}
			i++;
		}
	}
}

void close_door(t_info *info)
{
	int		px;
	int		py;
	int		i;

	px = (int)((info->player.pX + cos(info->player.angle) * 90)\
	 / info->TILE_SIZE);
	py = (int)((info->player.pY + sin(info->player.angle) * 90)\
	 / info->TILE_SIZE);
	i = 0;
	while (i < info->n_doors)
	{
		if (info->doors[i].door_x == px && info->doors[i].door_y == py)
		{
			info->doors[i].is_open = 0;
			info->map[py][px] = 2;
			break;
		}
		i++;
	}
}

int press(int keycode, void *inf)
{
	t_info	*info;

	info = inf;
	if (keycode == UP)
		info->keys.key_forward = 1;
	else if (keycode == DOWN)
		info->keys.key_back = 1;
	else if (keycode == LEFT)
		info->keys.key_left = 1;
	else if (keycode == RIGHT)
		info->keys.key_right = 1;
	else if (keycode == ROT_L)
		info->keys.key_rot_l = 1;
	else if (keycode == ROT_R)
		info->keys.key_rot_r = 1;
	else if (keycode == DOOR_OPEN)
		open_door(info);
	else if (keycode == DOOR_CLOSE)
		close_door(info);
	return (0);
}

int release(int keycode, void *inf)
{
	t_info	*info;

	info = inf;
	if (keycode == UP)
		info->keys.key_forward = 0;
	else if (keycode == DOWN)
		info->keys.key_back = 0;
	else if (keycode == LEFT)
		info->keys.key_left = 0;
	else if (keycode == RIGHT)
		info->keys.key_right = 0;
	else if (keycode == ROT_L)
		info->keys.key_rot_l = 0;
	else if (keycode == ROT_R)
		info->keys.key_rot_r = 0;
	return (0);
}

int mouse_move(int x, int y, void *inf)
{
    static int	last_x = -1;
    t_info 		*info;
    int			delta_x;
    
    (void)y;
    info = inf;
    if (last_x == -1)
        last_x = x;
    delta_x = x - last_x;
    last_x = x;
    info->player.angle += delta_x * ROT_SPEED;
    if (info->player.angle < 0)
        info->player.angle += 2 * PI;
    else if (info->player.angle >= 2 * PI)
        info->player.angle -= 2 * PI;
    return (0);
}

int main()
{
  t_info info;

  init_info(&info);
  mlx_hook(info.mlx.win, 3, 1L<<1, release, &info);
  mlx_hook(info.mlx.win, 2, 1L<<0, press, &info);
  mlx_hook(info.mlx.win, 6, 1L << 6, mouse_move, &info);
  mlx_loop_hook(info.mlx.con, raycasting, &info);
  mlx_loop(info.mlx.con);
}