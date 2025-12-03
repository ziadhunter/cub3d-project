#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include "mlx.h"  // MiniLibX functions (mlx_new_image, etc.)
#include <math.h> // sin, cos, tan, hypot, fabs, fmod, floor
#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <unistd.h>

// =================== DEFINES ===================
#define PI 3.14159265358979323846
#define TILE_SIZE 64
#define MINIMAP_SCALE 2
#define WIN_WIDTH 1080   // number of columns
#define WIN_HEIGHT 720  // number of rows
#define FOV 1.0471975512 // 60° field of view in radians
#define NUM_COLUMNS 1080 // how many rays to cast (e.g. screen width)
#define MIN_WALK_SPEED 0.5
#define MAX_WALK_SPEED 3
#define MIN_ROTATION_SPEED	(PI / 180) / 3
#define MAX_ROTATION_SPEED  (PI / 180)

// Colors (RGBA or 0x00RRGGBB depending on MLX build)
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define BLUE 0x0000FF

// Mini map macros
#define X_START_POINT (TILE_SIZE)
#define Y_START_POINT ((WIN_HEIGHT) / 3 * 2)
#define MAP_SIZE (((WIN_HEIGHT) / 3) - TILE_SIZE)
#define MAP_RADIUS (MAP_SIZE / 2)
#define CENTER_MAP_X (X_START_POINT + MAP_RADIUS)
#define CENTER_MAP_Y (Y_START_POINT + MAP_RADIUS)

#define LEFT 65361
#define RIGHT 65363
#define ESC 65307

#define DIRECTION_LENGTH 20         // length of player direction line
#define VERTICAL_RAY_THRESHOLD 1e-6 // epsilon for vertical ray checks

typedef struct s_coordinates
{
	double				x;
	double				y;
}					t_cord;

typedef struct s_facing_direction
{
	int		facing_up;
	int		facing_right;
}					t_facing;

typedef struct s_line
{
	char			*str;
	int				length;
	struct s_line	*next;
}					t_line;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_ray
{
	double				start_x;
	double				start_y;
	double				ray_angle;
	double				end_x;
	double				end_y;
}					t_ray;

typedef struct s_oldmove
{
	int				left;
	int				right;
	int				forw;
	int				back;
	int				turn_left;
	int				turn_right;
}					t_oldmove;

typedef struct s_player
{
	double			x;
	double			y;
	int				radius;
	int				back_forw;
	int				left_right;
	int				turn;
	double			rotation_angle;
	double			walking_speed;
	double			rotation_speed;
	t_oldmove		*old_move;
}					t_player;

typedef struct s_direction
{
	double			x;
	double			y;
}					t_direction;

typedef struct mlxcenter_x
{
	void			*init;
	void			*win;
}					t_mlx;

typedef struct s_db_po
{
	char			**ptr;
	char			**ptrr;
}					t_db_pointer;

typedef struct s_map
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				*f;
	int				*c;
	int				columns;
	int				rows;
	int				map_start;
}					t_map;

typedef struct s_data
{
	t_mlx			*mlx;
	t_img			new_image;
	t_player		*player;
	t_ray			**rays;
	t_map			*map_info;
}					t_data;

typedef struct s_element
{
	char			*type;
	int				length;
	void			(*handle)(t_map *map, char **str, char **lines, int i);
}					t_element;



/* PARSING FUNCTIONS */
void				add_ceiling(t_map *map, char **str, char **lines, int i);
void				add_we(t_map *map, char **str, char **lines, int i);
void				add_ea(t_map *map, char **str, char **lines, int i);
void				add_so(t_map *map, char **str, char **lines, int i);
void				add_no(t_map *map, char **str, char **lines, int i);
void				add_floor(t_map *map, char **str, char **lines, int i);
void				which_element(char **line, int index, t_map *map,
						t_element element[6]);
int					all_element_found(t_map *map);
int					quick_check(char *line);
t_map				*extract_element(char **lines);
void				free_double_pointer(char **value);
void				free_map(t_map *map);
void				free_data(t_data *data);
void				error_exit(t_map *map, char **value,
						t_db_pointer *double_pointers, char *str);
int					is_space_or_wall(char c);
int					is_space_or_nl(char c);
t_map				*initialize_map(void);
t_player			*initialize_player(char c, int x, int y);
void				initialize_element(t_element (*element)[6]);
void				find_empty_line(t_map *map_info, char **lines, char *line,
						int fd);
void				check_empty_line(t_map *map_info, char **lines,
						char *file_name);
char				**set_new_lines(int len, int characters, char **lines);
char				**rebuild_map_with_same_size(t_map *map, char **lines,
						int start);
t_data				*parsing_the_map(t_map *map_info, char **lines,
						char *file_name);
void				check_extension(char *file_name, char *ext, t_map *map_info,
						t_db_pointer *pointers);
char				**get_lines_of_file(int fd);
int					ft_atoi_c(const char *str);
int					is_map_element(char c);
void				invalid_position(t_map *map_info, t_player *player,
						char **lines, t_cord cor);
void				check_element_position(t_map *map_info, t_player **player,
						char **lines, t_cord cor);
void				check_space_position(t_map *map_info, t_player *player,
						char **lines, t_cord cor);
t_player			*valid_map(t_map *map_info, char **map, int i, int j);
t_data				*parsing(char *file_name);

/*KEY HANDLE*/
void	speed_adjustment(int key, t_data *data);
void	mouvement_adjustment(int key, t_data *data);
void	rotation_adjustment(int key, t_data *data);
void	rotation_release(int key, t_data *data);
void	mouvement_release(int key, t_data *data);
int		close_window(t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		key_release(int key, t_data *data);
int		key_press(int key, t_data *data);


/*RAY-CASTING*/
// void	render_rays(t_data *data, double x, double y, double z, double w);
void	facing_direction(double ray_angle, t_facing *dir);
int	wall(t_data *data, double x, double y);
void	insert_end_ray(t_ray *ray, t_direction *dir);
double	normalize_angle(double angle);
void	short_ray(t_data *data, t_ray *ray, t_direction *horizontal_inters,
		t_direction *vertical_inters);
void find_horizontal_intersiction(
	t_data *data, double ray_angle, t_facing facing, t_direction *horz_inter);
void find_vertical_intersiction(
	t_data *data, double ray_angle, t_facing facing, t_direction *vert_inter);
void	define_ray_position(t_data *data, double ray_angle, t_ray *ray);
void	creat_ray_casting(t_data *data);

/*PROJACTION*/
void	render_wall(t_data *data, int x, int y, int wall_hight);
void	projaction(t_data *data);

/*MINI MAP*/
void	base_of_mini_map(t_data *data);
void	mini_map(t_data *data, int x, int y, int color);
void	render_player_mini_map(t_data *data);
void	render_mini_map_rays(t_data *data, t_cord cord, double z, double w);
void	render_rays_mini_map(t_data *data, int i);
void	render_mini_map(t_data *data);


/* FUNCTIONS */
void	free_rays(t_ray **rays);
void	free_all_data_and_exit(t_data *data, char *str);
int		is_wall(t_data *data, double *x, double *y);
void	put_pixel(t_img *data, int x, int y, int color);
void	update_palyer_state(t_data *data, t_player *player);
int		the_animation(t_data *data);
void	initialize_rays(t_data *data);
void	initialization(t_data *data);
void	start_the_game(t_data *data);



