/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:28:59 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/19 00:40:24 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Cub3d header files */
# include <door.h>
# include <keys.h>
# include <libft.h>
# include <parsing.h>
# include <ray_cast.h>
# include <rendring.h>

/* =================== DEFINES =================== */
# define PI 3.14159265358979323846
# define TILE_SIZE 64
# define MINIMAP_SCALE 2
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FOV 1.0471975512
# define NUM_COLUMNS 1280
# define MIN_WALK_SPEED 0.5
# define MAX_WALK_SPEED 6
# define MIN_ROTATION_SPEED 0.003491
# define MAX_ROTATION_SPEED 0.017453

# define WEAPON_XPM_WIDTH 1280
# define WEAPON_XPM_HEIGHT 719

/* Colors */
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define BLUE 0x0000FF

/* Mini map macros */
# define X_START_POINT TILE_SIZE
# define Y_START_POINT 64
// # define MAP_SIZE (((WIN_HEIGHT) / 3) - TILE_SIZE)
// # define MAP_RADIUS (MAP_SIZE / 2)
// # define CENTER_MAP_X (X_START_POINT + MAP_RADIUS)
// # define CENTER_MAP_Y (Y_START_POINT + MAP_RADIUS)

# define DIRECTION_LENGTH 20         // length of player direction line
# define VERTICAL_RAY_THRESHOLD 1e-6 // epsilon for vertical ray checks

# define HORIZONTAL 1
# define VERTICAL 2

typedef enum e_cell_type
{
	NONE,
	WALL,
	DOOR
}				t_cell_type;

/* MLX */
typedef struct mlxcenter_x
{
	void		*init;
	void		*win;
}				t_mlx;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	t_img		close_door_btn;
	t_img		open_door_btn;
	t_img		door;
	t_img		door_inside;
	int			floor_color;
	int			ceil_color;
}				t_texture;

/* Game logic*/
typedef struct s_facing_direction
{
	int			facing_up;
	int			facing_right;
}				t_facing;

typedef struct s_coordinates
{
	double		x;
	double		y;
}				t_cord;

typedef struct s_icoordinates
{
	int			x;
	int			y;
}				t_icord;

typedef struct s_ray
{
	int			start_x;
	int			start_y;
	double		ray_angle;
	int			end_x;
	int			end_y;
	int			intersection;
	t_direction	ray_direction;
	t_img		*hit_cell;
	int			x_offset;
	int			y_offset;
}				t_ray;

typedef struct s_move
{
	int			now;
	int			before;
}				t_move;

typedef struct s_knife
{
	t_img		knife_move;
	t_img		knife_attack;
	int			knife_state;
	int			knif_m_i;
	int			knif_m_n;
	int			knif_a_i;
	int			knif_a_n;
}				t_knife;

typedef struct s_player
{
	double		x;
	double		y;
	int			radius;
	t_move		walk_direction;
	t_move		rotation_direction;
	t_move		side_direction;
	double		rotation_angle;
	double		walking_speed;
	double		rotation_speed;
	bool		is_looking_at_door;
	t_door		*door;
	t_knife		knife;
}				t_player;

typedef struct s_cell
{
	t_cell_type	cell_type;
	void		*options;
}				t_cell;

typedef struct s_data
{
	t_dlist		*doors_list;
	t_texture	textures;
	t_img		wall;
	t_mlx		*mlx;
	t_img		new_image;
	t_player	*player;
	t_ray		**rays;
	t_map_data	*map_info;
	t_cell		**map;
	bool		hide_mousse;
	int			map_s;
	int			map_r;
	t_cord		map_c;
}				t_data;

void			load_game_data(t_data *data);
void			start_the_game(t_data *data);
t_cell			**create_map(t_data *data, char **char_map);
void			update_palyer_state(t_data *data, t_player *player);
void			load_weapons(t_data *data);
void			load_xpm(t_data *data, char *path, t_img *img); /* xpm tool */

/* utils */
bool			file_exists(const char *path);
bool			file_readable(const char *path);
bool			file_is_not_dir(char *path);
bool			file_isvalid(char *path);
double			safe_tan(double n);

void			free_rays(t_ray **rays);
void			free_all_data_and_exit(t_data *data, char *str,
					int exit_status);

#endif