#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include "mlx.h"  // MiniLibX functions (mlx_new_image, etc.)
#include <math.h> // sin, cos, tan, hypot, fabs, fmod, floor
#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <unistd.h>
#include <stdbool.h>

// =================== DEFINES ===================
#define PI 3.14159265358979323846
#define TILE_SIZE 64
#define MINIMAP_SCALE 4
#define WIN_WIDTH 2080   // number of columns
#define WIN_HEIGHT 1440   // number of rows
#define FOV (60 * (PI / 180)) // 60° field of view in radians
#define NUM_COLUMNS 2080 // how many rays to cast (e.g. screen width)


#define MAP_WIDTH 26
#define MAP_HEIGHT 11

// Colors (RGBA or 0x00RRGGBB depending on MLX build)
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define BLUE 0x0000FF

// Mini map macros
#define X_START_POINT TILE_SIZE
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
	int				x;
	int				y;
}					t_cord;

typedef struct s_line
{
	char			*str;
	int				length;
	struct s_line	*next;
}					t_line;

#define HORIZONTAL 1
#define VERTICAL 2

typedef enum e_door_state
{
    OPENED,
    CLOSED
} t_door_state;

typedef enum e_cell_type
{
    NONE,
    SPACE,
    WALL,
    DOOR
} t_cell_type;

typedef struct s_direction
{
    double x;
    double y;
}   t_direction;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_texture
{
    t_img no;
    t_img so;
    t_img we;
    t_img ea;
    t_img door;
    t_img door_side;
    t_img close_door_btn;
    t_img open_door_btn;
} t_texture;

typedef struct s_ray
{
	int	start_x;
	int start_y;
	double ray_angle;
	int end_x;
	int end_y;
    /*
        TODO: add a variable to hold whether the ray is
                intersection verticaly or horisontaly
                will be used when applying texture to the walls
    */
   int intersection;
   t_direction ray_direction;
} t_ray;

typedef struct s_oldmove
{
	int				left;
	int				right;
	int				forw;
	int				back;
	int				turn_left;
	int				turn_right;
}					t_oldmove;

typedef struct s_direction
{
	double			x;
	double			y;
}					t_direction;

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
    bool is_looking_at_door;
}   t_player;

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
	int				map_length;
	int				map_height;
	int				map_start;
}					t_map;

// typedef struct s_door
// {
//     int x;
//     int y;
//     t_door_state state;
// } t_door;

// typedef struct s_entites
// {
//     t_door door;
// } t_entites;


typedef struct s_door
{
    bool is_valid;
    bool is_open;
} t_door;

typedef struct s_cell
{
    t_cell_type cell_type;
    void *options;
} t_cell;

typedef struct s_map
{
    t_cell **map;
    int w_map;
    int h_map;
} t_map;

typedef struct s_data
{
    t_texture   textures;
    t_img       wall;
    t_mlx       *mlx;
    t_img       new_image;
    t_player    *player;
	t_ray		**rays;
    // char        **map;
    t_map       map;
    // t_entites entites;
}   t_data;

typedef struct s_element
{
	char			*type;
	int				length;
	void			(*handle)(t_map *map, char **str, char **lines, int i);
}					t_element;

void				render_mini_map(t_data *data);
void				put_pixel(t_img *data, int x, int y, int color);
// t_ray				**creat_ray_casting(t_data *data);
double				normalize_angle(double angle);

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
t_player			*initialize(char c, t_player *player, t_oldmove *old);
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
// typedef struct s_map
// {
//     t_cell **map;
// } t_map;


void insert_end_ray(t_ray *ray, t_direction *dir, int intersection);
void short_ray(t_data * data, t_ray *ray, t_direction *horizontal_inters, t_direction *vertical_inters);
void render_rays(t_data *data, double x, double y, double z, double w);
void define_ray_position(t_data *data, double ray_angle, t_ray *ray);
t_ray **creat_ray_casting(t_data *data);
t_direction *find_vertical_intersiction(t_data *data, double ray_angle, int facing_up, int facing_right);
t_direction *find_horizontal_intersiction(t_data *data, double ray_angle, int facing_up, int facing_right);

t_direction *facing_direction(double ray_angle);
double normalize_angle(double angle);

void *load_xpm(t_data *data, char *path);

t_cell  **create_map(t_data *data, char **char_map);
