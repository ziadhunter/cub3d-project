#include <stdlib.h>     // malloc, free
#include <math.h>       // sin, cos, tan, hypot, fabs, fmod, floor
#include "mlx.h"        // MiniLibX functions (mlx_new_image, etc.)

#define PI 3.14159265358979323846
// =================== DEFINES ===================
#define TILE_SIZE 64
#define MAP_LENGTH 15   // number of columns
#define MAP_WIDTH 10    // number of rows
#define FOV (60 * (PI / 180)) // 60° field of view in radians
#define NUM_COLUMNS 300 // how many rays to cast (e.g. screen width)

// Colors (RGBA or 0x00RRGGBB depending on MLX build)
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED   0xFF0000
#define BLUE  0x0000FF

#define DIRECTION_LENGTH 20          // length of player direction line
#define VERTICAL_RAY_THRESHOLD 1e-6  // epsilon for vertical ray checks

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
}   t_img;

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

typedef struct mlx
{
    void *init;
    void *win;
} t_mlx;

typedef struct s_data
{
    t_mlx       *mlx;
    t_img       new_image;
    t_player    *player;
    char        **map;
}   t_data;
t_player *initialize()
{
    t_player *player;
    t_oldmove *old;
    old = malloc(sizeof(t_oldmove));
    old->back = 0;
    old->forw = 0;
    old->left = 0;
    old->right = 0;
    old->turn_left = 0;
    old->turn_right = 0;
    player = malloc(sizeof(t_player));
    player->old_move = old;
    player->x = 7 * 64;
    player->y = 5 * 64;
    player->radius = 15;
    player->back_forw = 0;
    player->left_right = 0;
    player->rotation_angle = PI / 2;
    player->walking_speed = 1;
    player->rotation_speed = (PI / 180) / 2;
    return(player);
}

void put_pixel(t_img *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

void render_static_map(t_data *data)
{
    int color;

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 15; col++)
        {
            color = WHITE;
            if (data->map[row][col] == '1')
                color = BLACK;
            for (int y = 0; y < TILE_SIZE; y++)
            {
                for (int x = 0; x < TILE_SIZE; x++)
                {
                    put_pixel(&data->new_image, col * TILE_SIZE + x,
                        row * TILE_SIZE + y, color);
                }
            }
        }
    }
}

t_direction *find_direction(t_data *data)
{
    t_direction *dir;

    dir = malloc(sizeof(t_direction));
    if (!dir)
        return (NULL);
    if (data->player->turn == 1)
        data->player->rotation_angle += data->player->rotation_speed;
    else if (data->player->turn == -1)
        data->player->rotation_angle -= data->player->rotation_speed;
    dir->x = data->player->x + cos(data->player->rotation_angle)
        * DIRECTION_LENGTH;
    dir->y = data->player->y + sin(data->player->rotation_angle)
        * DIRECTION_LENGTH;
    return (dir);
}

void render_direction(t_data *data, t_direction *dir)
{
    double x = data->player->x;
    double y = data->player->y;
    double xi;
    double yi;
    double z = dir->x;
    double w = dir->y;
    int step;

    if (fabs(z - x) > fabs(w - y))
        step = fabs(z - x);
    else
        step = fabs(w - y);
    xi = (z - x) / step;
    yi = (w - y) / step;
    for (int i = 0; i < step; i++)
    {
        put_pixel(&data->new_image, x, y, BLUE);
        put_pixel(&data->new_image, x + 1, y, BLUE);
        put_pixel(&data->new_image, x, y + 1, BLUE);
        put_pixel(&data->new_image, x, y - 1, BLUE);
        put_pixel(&data->new_image, x -1, y, BLUE);       
        x += xi;
        y += yi;
    }
}

int wall(t_data *data, double x, double y)
{
    double rx = x / TILE_SIZE;
    double ry = y / TILE_SIZE;

    if (data->map[(int)ry][(int)rx] != '0')
        return (1);
    return (0);
}

t_direction *find_horizontal_intersiction(
    t_data *data, double ray_angle, int facing_up, int facing_right)
{
    double x_step;
    double y_step;
    double x_intr;
    double y_intr;
    t_direction *dir;

    dir = malloc(sizeof(t_direction));
    if (!dir)
        return (NULL);
    if (fabs(tan(ray_angle)) < 1e-6)
    {
        free(dir);
        return (NULL);
    }
    y_intr = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
    if (!facing_up)
        y_intr += TILE_SIZE;
    x_intr = ((y_intr - data->player->y) / tan(ray_angle))
        + data->player->x;
    y_step = TILE_SIZE;
    if (facing_up)
        y_step *= -1;
    x_step = TILE_SIZE / tan(ray_angle);
    if ((x_step > 0 && !facing_right) || (x_step < 0 && facing_right))
        x_step *= -1;
    if (facing_up)
        y_intr--;
    while (x_intr >= 0 && x_intr < MAP_LENGTH * TILE_SIZE
        && y_intr >= 0 && y_intr < MAP_WIDTH * TILE_SIZE)
    {
        if (wall(data, x_intr, y_intr))
        {
            dir->x = x_intr;
            dir->y = y_intr;
            return dir;
        }
        x_intr += x_step;
        y_intr += y_step;
    }
    return NULL;
}

t_direction *find_vertical_intersiction(
    t_data *data, double ray_angle, int facing_up, int facing_right)
{
    double x_step;
    double y_step;
    double x_intr;
    double y_intr;
    t_direction *dir;

    if (fabs(cos(ray_angle)) < VERTICAL_RAY_THRESHOLD)
        return (NULL);
    dir = malloc(sizeof(t_direction));
    if (!dir)
        return (NULL);
    x_intr = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
    if (facing_right)
        x_intr += TILE_SIZE;
    y_intr = data->player->y + (x_intr - data->player->x) * tan(ray_angle);
    x_step = TILE_SIZE;
    if (!facing_right)
        x_step *= -1;
    y_step = TILE_SIZE * tan(ray_angle);
    if ((y_step > 0 && facing_up) || (y_step < 0 && !facing_up))
        y_step *= -1;
    if (!facing_right)
        x_intr--;
    while (x_intr >= 0 && x_intr < MAP_LENGTH * TILE_SIZE
        && y_intr >= 0 && y_intr < MAP_WIDTH * TILE_SIZE)
    {
        if (wall(data, x_intr, y_intr))
        {
            dir->x = x_intr;
            dir->y = y_intr;
            return dir;
        }
        x_intr += x_step;
        y_intr += y_step;
    }
    return NULL;
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return (angle);
}

t_direction *facing_direction(double ray_angle)
{
    t_direction *dir;

    dir = malloc(sizeof(t_direction));
    if (!dir)
        return (NULL);
    dir->x = (ray_angle > 0 && ray_angle < PI) ? 0 : 1;
    dir->y = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI) ? 1 : 0;
    return (dir);
}

void define_ray_position(t_data *data, double ray_angle)
{
    if (ray_angle > 2 * PI || ray_angle < 0)
        ray_angle = normalize_angle(ray_angle);
    t_direction *dir = facing_direction(ray_angle);
    t_direction *horizontal_intersiction =
        find_horizontal_intersiction(data, ray_angle, dir->x, dir->y);
    t_direction *vertical_intersiction =
        find_vertical_intersiction(data, ray_angle, dir->x, dir->y);
    if (horizontal_intersiction && vertical_intersiction)
    {
        double dist_h = hypot(horizontal_intersiction->x - data->player->x,
                horizontal_intersiction->y - data->player->y);
        double dist_v = hypot(vertical_intersiction->x - data->player->x,
                vertical_intersiction->y - data->player->y);
        if (dist_h < dist_v)
            render_direction(data, horizontal_intersiction);
        else
            render_direction(data, vertical_intersiction);
    }
    else if (horizontal_intersiction)
        render_direction(data, horizontal_intersiction);
    else if (vertical_intersiction)
        render_direction(data, vertical_intersiction);
    free(dir);
    free(horizontal_intersiction);
    free(vertical_intersiction);
}

void render_ray_casting(t_data *data)
{
    double ray_angle;
    int column;

    column = 0;
    ray_angle = data->player->rotation_angle - (FOV / 2);
    while (column < NUM_COLUMNS)
    {
        define_ray_position(data, ray_angle);
        ray_angle += FOV / NUM_COLUMNS;
        column++;
    }
}

int is_wall(t_data *data, double *x, double *y)
{
    double px = data->player->x / TILE_SIZE;
    double py = data->player->y / TILE_SIZE;
    double rx = *x / TILE_SIZE;
    double ry = *y / TILE_SIZE;

    if (data->map[(int)ry][(int)rx] != '1')
        return (1);
    else if (data->map[(int)ry][(int)px] != '1')
    {
        *x = data->player->x;
        return (1);
    }
    else if (data->map[(int)py][(int)rx] != '1')
    {
        *y = data->player->y;
        return (1);
    }
    return (0);
}

void find_position(t_data *data, t_player *player)
{
    double x = player->x;
    double y = player->y;

    if (player->back_forw == -1)
    {
        x -= cos(player->rotation_angle) * player->walking_speed / 3;
        y -= sin(player->rotation_angle) * player->walking_speed / 3;
    }
    else if (player->back_forw == 1)
    {
        x += cos(player->rotation_angle) * player->walking_speed / 3;
        y += sin(player->rotation_angle) * player->walking_speed / 3;
    }
    if (player->left_right == -1)
    {
        x += cos(player->rotation_angle - PI / 2) * player->walking_speed / 3;
        y += sin(player->rotation_angle - PI / 2) * player->walking_speed / 3;
    }
    else if (player->left_right == 1)
    {
        x += cos(player->rotation_angle + PI / 2) * player->walking_speed / 3;
        y += sin(player->rotation_angle + PI / 2) * player->walking_speed / 3;
    }
    if (is_wall(data, &x, &y))
    {
        player->x = x;
        player->y = y;
    }
}

void render_player(t_data *data)
{
    find_position(data, data->player);
    int cx = data->player->x;
    int cy = data->player->y;
    int x = cx - data->player->radius;
    int y = cy - data->player->radius;
    int r = data->player->radius;
    t_direction *dir;

    render_ray_casting(data);
    while (x <= cx + data->player->radius)
    {
        y = cy - data->player->radius;
        while (y <= cy + data->player->radius)
        {
            if (((x - cx) * (x - cx) + (y - cy) * (y - cy)) <= (r * r))
                put_pixel(&data->new_image, x, y, RED);
            y++;
        }
        x++;
    }
    if (data->player->rotation_angle > 2 * PI
        || data->player->rotation_angle < 0)
        data->player->rotation_angle = normalize_angle(data->player->rotation_angle);
    dir = find_direction(data);
    free(dir);
    // render_direction(data, dir);
}

int the_animation(t_data *data)
{
    static unsigned int l = 0;
    int i;
    int j;
    t_img new_image;

    i = 0;
    j = 0;
    new_image.img = mlx_new_image(data->mlx->init,
            TILE_SIZE * MAP_LENGTH, TILE_SIZE * 10);
    new_image.addr = mlx_get_data_addr(new_image.img,
            &new_image.bpp, &new_image.line_length, &new_image.endian);
    data->new_image = new_image;
    render_static_map(data);
    render_player(data);
    mlx_put_image_to_window(data->mlx->init, data->mlx->win, new_image.img, 0, 0);
    mlx_destroy_image(data->mlx->init, data->new_image.img);
    data->new_image.img = NULL;
    l++;
    return (0);
}

void	move_back(t_player *player)
{
	player->x -= cos(player->rotation_angle) * player->walking_speed;
	player->y -= sin(player->rotation_angle) * player->walking_speed;
}

void	move_forward(t_player *player)
{
	player->x += cos(player->rotation_angle) * player->walking_speed;
	player->y += sin(player->rotation_angle) * player->walking_speed;
}

void	move_left(t_player *player)
{
	player->x += cos(player->rotation_angle - PI / 2) * player->walking_speed;
	player->y += sin(player->rotation_angle - PI / 2) * player->walking_speed;
}

void	move_right(t_player *player)
{
	player->x += cos(player->rotation_angle + PI / 2) * player->walking_speed;
	player->y += sin(player->rotation_angle + PI / 2) * player->walking_speed;
}
# define LEFT 65361
# define RIGHT 65363


int	key_press(int key, t_data *data)
{
	// if (key == ESC)
	// 	free_all_data_and_exit(data, "you exit the game!!\n");
	// if (data->map->player.movement == 1)
	// 	return (0);

	if (key == 'a')
    {
        data->player->old_move->left = 1;
		data->player->left_right = -1;
    }
	else if (key == 'd')
    {
        data->player->old_move->right = 1;
		data->player->left_right = 1;
    }
	else if (key == 's')
    {
        data->player->old_move->back = 1;
		data->player->back_forw = -1;
    }
	else if (key == 'w')
    {
        data->player->old_move->forw = 1;
		data->player->back_forw = 1;
    }

	if (key == LEFT)
    {
        data->player->old_move->turn_left = 1;
		data->player->turn = -1;
    }
	else if (key == RIGHT)
    {
        data->player->old_move->turn_right = 1;
		data->player->turn = 1;
    }

	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 'a')
    {
        data->player->old_move->left = 0;
        if (data->player->old_move->right)
		    data->player->left_right = 1;
        else
            data->player->left_right = 0;
    }
	else if (key == 'd')
    {
        data->player->old_move->right = 0;
        if (data->player->old_move->left)
		    data->player->left_right = -1;
        else
            data->player->left_right = 0;
    }
	else if (key == 's')
    {
        data->player->old_move->back = 0;
        if (data->player->old_move->forw)
		    data->player->back_forw = 1;
        else
            data->player->back_forw = 0;
    }
	else if (key == 'w')
    {
        data->player->old_move->forw = 0;
        if (data->player->old_move->forw)
		    data->player->back_forw = 1;
        else
            data->player->back_forw = 0;
    }

	if (key == LEFT)
    {
        data->player->old_move->turn_left = 0;
        if (data->player->old_move->turn_right)
		    data->player->turn = 1;
        else
            data->player->turn = 0;
    }
	else if (key == RIGHT)
    {
        data->player->old_move->turn_right = 0;
        if (data->player->old_move->turn_left)
		    data->player->turn = -1;
        else
            data->player->turn = 0;
    }

	return (0);
}


int	main(void)
{
	t_data	*data;
	t_mlx	*mlx;
	char	*map[] =
	{
		"111111111111111",
		"100011001000101",
		"101000001110001",
		"101001111000101",
		"101000000000101",
		"101000001111001",
		"101000001111111",
		"100011001000001",
		"100000000000001",
		"111111111111111"
	};

	data = malloc(sizeof(t_data));
	mlx = malloc(sizeof(t_mlx));
	data->map = map;
	data->mlx = mlx;
	data->player = initialize();

	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, 64 * 15, 64 * 10, "3D game");

	mlx_hook(mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, data);
	// mlx_hook(mlx->win, 2, 0, turn_press, data);

	mlx_loop_hook(mlx->init, the_animation, data);
	mlx_loop(mlx->init);
}
