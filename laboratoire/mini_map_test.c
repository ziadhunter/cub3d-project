#include "cub.h"

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
    player->x = 17 * 64 - 32;
    player->y = 5 * 64 - 32;
    player->radius = 6;
    player->back_forw = 0;
    player->left_right = 0;
    player->rotation_angle = PI / 2;
    player->walking_speed = 2;
    player->rotation_speed = (PI / 180) / 2;
    return(player);
}

void put_pixel(t_img *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
        return;
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}
// void render_static_map(t_data *data)
// {
//     int color;

//     for (int row = 0; row < MAP_HEIGHT; row++)
//     {
//         for (int col = 0; col < MAP_WIDTH; col++)
//         {
//             color = WHITE;
//             if (data->map[row][col] == '1')
//                 color = BLACK;
//             for (int y = 0; y < TILE_SIZE; y++)
//             {
//                 for (int x = 0; x < TILE_SIZE; x++)
//                 {
//                     put_pixel(&data->new_image, col * TILE_SIZE + x,
//                         row * TILE_SIZE + y, color);
//                 }
//             }
//         }
//     }
// }




// // void free_old_rays(t_ray **rays)
// // {
// // 	int i;

// // 	i = 0;
// // 	while (i < NUM_COLUMNS)
// // 		free(rays[i++]);
// // 	free(rays);
// // } 

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return (angle);
}





// void render_player(t_data *data)
// {
//     int cx = data->player->x;
//     int cy = data->player->y;
//     int x = cx - data->player->radius;
//     int y = cy - data->player->radius;
//     int r = data->player->radius;



//     while (x <= cx + data->player->radius)
//     {
//         y = cy - data->player->radius;
//         while (y <= cy + data->player->radius)
//         {
//             if (((x - cx) * (x - cx) + (y - cy) * (y - cy)) <= (r * r))
//                 put_pixel(&data->new_image, x, y, RED);
//             y++;
//         }
//         x++;
//     }
//     if (data->player->rotation_angle > 2 * PI
//         || data->player->rotation_angle < 0)
//         data->player->rotation_angle = normalize_angle(data->player->rotation_angle);

// }
void render_wall(t_data *data, int x, int y, int wall_hight)
{
    int i = 0;
    int tmp;

    tmp = y + wall_hight;

    // printf("wall h: %d\n", wall_hight);
    // printf("w: %d\n", y);
    while (i < y)
    {
        put_pixel(&data->new_image, x, i, WHITE);
        i++;
    }
    // printf("b: %d\n", tmp);
    while ( i < tmp)
    {
        put_pixel(&data->new_image, x, i, BLUE);
        i++;
    }
    // printf("d: %d\n", WIN_HEIGHT);
    while (i < WIN_HEIGHT)
    {
        put_pixel(&data->new_image, x, i, BLACK);
        i++;
    }
}
void projaction (t_data *data)
{
    int i = 0;
    double ray_distance;
    double distanceProjactionPlane;
    double wall_hight;
    t_ray *ray;
    distanceProjactionPlane = ((MAP_WIDTH * TILE_SIZE) / 2) / tan(FOV * 2/3);
    while (i < NUM_COLUMNS)
    {
        ray = data->rays[i];
        ray_distance = hypot(ray->end_x - ray->start_x, ray->end_y - ray->start_y);
        wall_hight = (TILE_SIZE / ray_distance) * distanceProjactionPlane;
        if (wall_hight > 720)
            wall_hight = 720;
        render_wall(data, i, (WIN_HEIGHT / 2) - ((int)wall_hight / 2), (int)wall_hight);
        i++;
    }
}

void clear_window(t_data * data)
{
    int i;
    int j;

    i = 0;
    j= 0;
    while (j < WIN_HEIGHT)
    {
        i = 0;
        while (i < WIN_WIDTH)
        {
            if (j < (WIN_HEIGHT) / 2)
                put_pixel(&data->new_image, i, j, WHITE);
            else
                put_pixel(&data->new_image, i, j, BLACK);
            i++;
        }
        j++;
    }
}

int is_position_wall(t_data *data, double x, double y)
{
    double map_x = x / TILE_SIZE;
    double map_y = y / TILE_SIZE;
    
    if (map_x < 0 || map_y < 0 || map_x >= MAP_WIDTH || map_y >= MAP_HEIGHT)
        return (1);
    
    return (data->map[(int)map_y][(int)map_x] == '1');
}


void update_palyer_state(t_data *data, t_player *player)
{
    double x = player->x;
    double y = player->y;

    //update the x and y position of the player
    x += ((cos(player->rotation_angle) * player->walking_speed / 3) * player->back_forw);
    y += ((sin(player->rotation_angle) * player->walking_speed / 3) * player->back_forw);
    x += ((cos(player->rotation_angle + PI / 2) * player->walking_speed / 3) * player->left_right);
    y += ((sin(player->rotation_angle + PI / 2) * player->walking_speed / 3) * player->left_right);

    // check if the new position isn't a wall by checking X axis then Y axis
    if (!is_position_wall(data, x, player->y))
        player->x = x;
    if (!is_position_wall(data, player->x, y))
        player->y = y;

    //update the direction of the player
    data->player->rotation_angle += (data->player->rotation_speed * data->player->turn);
}

void free_old_rays(t_ray **rays)
{
	int i;

	i = 0;
	while (i < NUM_COLUMNS)
		free(rays[i++]);
	free(rays);
} 


int the_animation(t_data *data)
{
    static unsigned int l = 0;
    int i;
    int j;

    i = 0;
    j = 0;
    // clear_window(data);
    update_palyer_state(data, data->player);
	data->rays = creat_ray_casting(data);
    projaction(data);
    render_mini_map(data);
    mlx_put_image_to_window(data->mlx->init, data->mlx->win, data->new_image.img, 0, 0);
    l++;
	// free_old_rays(data->rays);
    return (0);
    // render_static_map(data);
    // render_player(data);
}

void free_all_data_and_exit(t_data *data, char *str)
{
    mlx_destroy_image(data->mlx->init, data->new_image.img);
    free(data->mlx);
    free(data->player->old_move);
    free(data->player);
    free(data);
    printf("%s", str);
    exit(0);
}

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		free_all_data_and_exit(data, "you exit the game!!\n");

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
        if (data->player->old_move->back)
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
    t_img new_image;
char *map[] = {
    "11111111111111111111111111",
    "10000000000000000000000001",
    "10000000010000000000000001",
    "10000000100000000000000001",
    "10000000000000000001000001",
    "10000011000000000000000001",
    "10000000000100000000000001",
    "10000000000100000001000001",
    "10000001000000000000000001",
    "10000000000000000000000001",
    "11111111111111111111111111"
};
	data = malloc(sizeof(t_data));
	mlx = malloc(sizeof(t_mlx));
	data->mlx = mlx;
	mlx->init = mlx_init();
	mlx->win = mlx_new_window(mlx->init, WIN_WIDTH, WIN_HEIGHT, "3D game");
    new_image.img = mlx_new_image(data->mlx->init, WIN_WIDTH, WIN_HEIGHT);
    new_image.addr = mlx_get_data_addr(new_image.img,
            &new_image.bpp, &new_image.line_length, &new_image.endian);
    data->new_image = new_image;

	data->map = map;
	data->rays = NULL;
	data->player = initialize();


	mlx_hook(mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, data);
	// mlx_hook(mlx->win, 2, 0, turn_press, data);

	mlx_loop_hook(mlx->init, the_animation, data);
	mlx_loop(mlx->init);
}

// void update_palyer_state(t_data *data, t_player *player)
// {
//     double x = player->x;
//     double y = player->y;

//     //update the x and y position of the player
//     x += ((cos(player->rotation_angle) * player->walking_speed / 3) * player->back_forw);
//     y += ((sin(player->rotation_angle) * player->walking_speed / 3) * player->back_forw);
//     x += ((cos(player->rotation_angle + PI / 2) * player->walking_speed / 3) * player->left_right);
//     y += ((sin(player->rotation_angle + PI / 2) * player->walking_speed / 3) * player->left_right);

//     //check if the new position isn't a wall
//     if (is_wall(data, &x, &y))
//     {
//         player->x = x;
//         player->y = y;
//     }

//     //update the direction of the player
//     data->player->rotation_angle += (data->player->rotation_speed * data->player->turn);
// }