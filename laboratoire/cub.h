#include <stdlib.h>     // malloc, free
#include <stdio.h>
#include <unistd.h>
#include <math.h>       // sin, cos, tan, hypot, fabs, fmod, floor
#include "mlx.h"      // MiniLibX functions (mlx_new_image, etc.)
#include "./gnl/get_next_line.h"
#include "./libft/libft.h"

// =================== DEFINES ===================
#define PI 3.14159265358979323846
#define TILE_SIZE 64
#define MINIMAP_SCALE 2
#define WIN_WIDTH 2080   // number of columns
#define WIN_HEIGHT 1440   // number of rows
#define FOV 1.0471975512 // 60° field of view in radians
#define NUM_COLUMNS 2080 // how many rays to cast (e.g. screen width)


#define MAP_WIDTH 26
#define MAP_HEIGHT 11

// Colors (RGBA or 0x00RRGGBB depending on MLX build)
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED   0xFF0000
#define BLUE  0x0000FF

// Mini map macros
#define X_START_POINT (TILE_SIZE)
#define Y_START_POINT ((WIN_HEIGHT) / 3 * 2)
#define MAP_SIZE (((WIN_HEIGHT) / 3) - TILE_SIZE)
#define MAP_RADIUS (MAP_SIZE / 2)
#define CENTER_MAP_X (X_START_POINT + MAP_RADIUS)
#define CENTER_MAP_Y (Y_START_POINT + MAP_RADIUS)

# define LEFT 65361
# define RIGHT 65363
# define ESC 65307


#define DIRECTION_LENGTH 20          // length of player direction line
#define VERTICAL_RAY_THRESHOLD 1e-6  // epsilon for vertical ray checks

typedef struct s_line
{
    char    *str;
    int     length;
    struct s_line *next;
} t_line;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_ray
{
	int	start_x;
	int start_y;
	double ray_angle;
	int end_x;
	int end_y;
} t_ray;

typedef struct s_oldmove
{
    int left;
    int right;
    int forw;
    int back;
    int turn_left;
    int turn_right;
} t_oldmove; 
 
typedef struct s_player
{
    double  x;
    double  y;
    int     radius;
    int     back_forw;
    int     left_right;
    int     turn;
    double  rotation_angle;
    double  walking_speed;
    double  rotation_speed;
    t_oldmove *old_move;
}   t_player;

typedef struct s_direction
{
    double x;
    double y;
}   t_direction;

typedef struct mlxcenter_x
{
    void *init;
    void *win;
} t_mlx;


typedef struct s_map
{
    char **map;
    char *no;
    char *so;
    char *we;
    char *ea;
    int    *f;
    int *c;
    int map_width;
    int map_height;
    char *line;
} t_map;

typedef struct s_data
{
    t_mlx       *mlx;
    t_img       new_image;
    t_player    *player;
	t_ray		**rays;
    t_map        *map;
}   t_data;

typedef struct s_element
{
    char *type;
    int length;
    void (*handle)(t_map *map, char **str, int fd);
} t_element;


t_player *initialize(char c, t_player *player, t_oldmove *old);
void render_mini_map(t_data *data);
void put_pixel(t_img *data, int x, int y, int color);
t_ray **creat_ray_casting(t_data *data);
double normalize_angle(double angle);