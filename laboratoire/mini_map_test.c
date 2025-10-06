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
    player->x = 7 * 64;
    player->y = 5 * 64;
    player->radius = 9;
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

    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
    {
        return;
    }
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

// int wall(t_data *data, double x, double y)
// {
//     double rx = x / TILE_SIZE;
//     double ry = y / TILE_SIZE;

//     if (data->map[(int)ry][(int)rx] != '0')
//         return (1);
//     return (0);
// }

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
    while (x_intr >= 0 && x_intr < MAP_WIDTH * TILE_SIZE
        && y_intr >= 0 && y_intr < MAP_HEIGHT * TILE_SIZE)
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

// t_direction *find_vertical_intersiction(
//     t_data *data, double ray_angle, int facing_up, int facing_right)
// {
//     double x_step;
//     double y_step;
//     double x_intr;
//     double y_intr;
//     t_direction *dir;

//     if (fabs(cos(ray_angle)) < VERTICAL_RAY_THRESHOLD)
//         return (NULL);
//     dir = malloc(sizeof(t_direction));
//     if (!dir)
//         return (NULL);
//     x_intr = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
//     if (facing_right)
//         x_intr += TILE_SIZE;
//     y_intr = data->player->y + (x_intr - data->player->x) * tan(ray_angle);
//     x_step = TILE_SIZE;
//     if (!facing_right)
//         x_step *= -1;
//     y_step = TILE_SIZE * tan(ray_angle);
//     if ((y_step > 0 && facing_up) || (y_step < 0 && !facing_up))
//         y_step *= -1;
//     if (!facing_right)
//         x_intr--;
//     while (x_intr >= 0 && x_intr < MAP_WIDTH * TILE_SIZE
//         && y_intr >= 0 && y_intr < MAP_HEIGHT * TILE_SIZE)
//     {
//         if (wall(data, x_intr, y_intr))
//         {
//             dir->x = x_intr;
//             dir->y = y_intr;
//             return dir;
//         }
//         x_intr += x_step;
//         y_intr += y_step;
//     }
//     return NULL;
// }

// double normalize_angle(double angle)
// {
//     angle = fmod(angle, 2 * PI);
//     if (angle < 0)
//         angle += 2 * PI;
//     return (angle);
// }


// void insert_end_ray(t_ray *ray, t_direction *dir)
// {
// 	ray->end_x = dir->x;
// 	ray->end_y = dir->y;
// }

// // void short_ray(t_data * data, t_ray *ray, t_direction *horizontal_inters, t_direction *vertical_inters)
// // {
// // 	double dist_h;
// // 	double dist_v;

// // 	if (horizontal_inters && vertical_inters)
// //     {
// int is_wall(t_data *data, double *x, double *y)
// {
//     double px = data->player->x / TILE_SIZE;
//     double py = data->player->y / TILE_SIZE;
//     double rx = *x / TILE_SIZE;
//     double ry = *y / TILE_SIZE;

//     if (data->map[(int)ry][(int)rx] != '1')
//         return (1);
//     else if (data->map[(int)ry][(int)px] != '1')
//     {
//         *x = data->player->x;
//         return (1);
//     }
//     else if (data->map[(int)py][(int)rx] != '1')
//     {
//         *y = data->player->y;
//         return (1);
//     }
//     return (0);
// }


// void free_old_rays(t_ray **rays)
// {
// 	int i;

// 	i = 0;
// 	while (i < NUM_COLUMNS)
// 		free(rays[i++]);
// 	free(rays);
// } 
// //         dist_h = hypot(horizontal_inters->x - data->player->x,
// //                 horizontal_inters->y - data->player->y);
// //         dist_v = hypot(vertical_inters->x - data->player->x,
// //                 vertical_inters->y - data->player->y);
// //         if (dist_h < dist_v)
// //             insert_end_ray(ray, horizontal_inters);
// //         else
// //             insert_end_ray(ray, vertical_inters);
// //     }
// //     else if (horizontal_inters)
// //         insert_end_ray(ray, horizontal_inters);
// //     else if (vertical_inters)
// //         insert_end_ray(ray, vertical_inters);
// // }

// void render_rays(t_data *data, double x, double y, double z, double w)
// {
//     double xi;
//     double yi;
//     int step;

//     if (fabs(z - x) > fabs(w - y))
//         step = fabs(z - x);
//     else
//         step = fabs(w - y);
//     xi = (z - x) / step;
//     yi = (w - y) / step;
//     for (int i = 0; i < step; i++)
//     {
//         put_pixel(&data->new_image, x, y, BLUE);
//         put_pixel(&data->new_image, x + 1, y, BLUE);
//         put_pixel(&data->new_image, x, y + 1, BLUE);
//         put_pixel(&data->new_image, x, y - 1, BLUE);
//         put_pixel(&data->new_image, x -1, y, BLUE);       
//         x += xi;
//         y += yi;
//     }
// }
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
void define_ray_position(t_data *data, double ray_angle, t_ray *ray)
{
    t_direction *dir;
    t_direction *horizontal_inters;
    t_direction *vertical_inters;

	dir = facing_direction(ray_angle);
    horizontal_inters = find_horizontal_intersiction(data, ray_angle, dir->x, dir->y);
    vertical_inters = find_vertical_intersiction(data, ray_angle, dir->x, dir->y);
	short_ray(data, ray, horizontal_inters, vertical_inters);
    // render_rays(data, data->player->x, data->player->y, ray->end_x, ray->end_y);
    free(dir);
    free(horizontal_inters);
    free(vertical_inters);
}

t_ray **creat_ray_casting(t_data *data)
{
    double ray_angle;
    int column;
	t_ray **rays;

	rays = malloc(sizeof(t_ray *) * NUM_COLUMNS);
	if (!rays)
    	return NULL;
	for (int i = 0; i < NUM_COLUMNS; i++)
	{
		rays[i] = malloc(sizeof(t_ray));
		if (!rays[i])
			return NULL; 
	}
    column = 0;
    ray_angle = data->player->rotation_angle - (FOV / 2);
    while (column < NUM_COLUMNS)
    {
		if (ray_angle > 2 * PI || ray_angle < 0)
        	ray_angle = normalize_angle(ray_angle);
		rays[column]->ray_angle = ray_angle;
		rays[column]->start_x = data->player->x;
		rays[column]->start_y = data->player->y;
        define_ray_position(data, ray_angle, rays[column]);

        ray_angle += FOV / NUM_COLUMNS;
        column++;
    }
	return(rays);
}



// void free_old_rays(t_ray **rays)
// {
// 	int i;

// 	i = 0;
// 	while (i < NUM_COLUMNS)
// 		free(rays[i++]);
// 	free(rays);
// } 


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
// void render_wall(t_data *data, double x, double y, double z, double w)
// {
//     double xi;
//     double yi;
//     int step;

//     // if (fabs(z - x) > fabs(w - y))
//     //     step = fabs(z - x);
//     // else
//     step = fabs(w - y);
//     xi = (z - x) / step;
//     yi = (w - y) / step;
//     for (int i = 0; i < step; i++)
//     {
//         put_pixel(&data->new_image, x, y, BLUE);
//         put_pixel(&data->new_image, x + 1, y, BLUE);
//         put_pixel(&data->new_image, x + 2, y, BLUE);
//         put_pixel(&data->new_image, x + 3, y, BLUE);
//         put_pixel(&data->new_image, x + 4, y, BLUE);
//         put_pixel(&data->new_image, x + 5, y, BLUE);
//         // put_pixel(&data->new_image, x, y + 1, BLUE);
//         // put_pixel(&data->new_image, x, y - 1, BLUE);
//         // put_pixel(&data->new_image, x -1, y, BLUE);       
//         x += xi;
//         y += yi;
//     }
// }
// void projaction (t_data *data)
// {
//     int i = 0;
//     double ray_distance;
//     double distanceProjactionPlane;
//     double wall_hight;
//     t_ray *ray;
//     distanceProjactionPlane = ((MAP_WIDTH * TILE_SIZE) / 2) / tan(FOV/2);
//     while (i < NUM_COLUMNS)
//     {
//         ray = data->rays[i];
//         ray_distance = hypot(ray->end_x - ray->start_x, ray->end_y - ray->start_y);
//         wall_hight = (TILE_SIZE / ray_distance) * distanceProjactionPlane;
//         render_wall(data, (MAP_WIDTH / NUM_COLUMNS) * i, (MAP_HEIGHT / 2) - (wall_hight / 2),
//             (MAP_WIDTH / NUM_COLUMNS) * i , (MAP_HEIGHT / 2) - (wall_hight /2) + wall_hight);
//         i++;
//     }
// }

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
void update_palyer_state(t_data *data, t_player *player)
{
    double x = player->x;
    double y = player->y;

    //update the x and y position of the player
    x += ((cos(player->rotation_angle) * player->walking_speed / 3) * player->back_forw);
    y += ((sin(player->rotation_angle) * player->walking_speed / 3) * player->back_forw);
    x += ((cos(player->rotation_angle + PI / 2) * player->walking_speed / 3) * player->left_right);
    y += ((sin(player->rotation_angle + PI / 2) * player->walking_speed / 3) * player->left_right);

    //check if the new position isn't a wall
    if (is_wall(data, &x, &y))
    {
        player->x = x;
        player->y = y;
    }

    //update the direction of the player
    data->player->rotation_angle += (data->player->rotation_speed * data->player->turn);
}


int the_animation(t_data *data)
{
    static unsigned int l = 0;
    int i;
    int j;

    i = 0;
    j = 0;
    clear_window(data);
    update_palyer_state(data, data->player);
	data->rays = creat_ray_casting(data);
    // projaction(data);
    // render_player(data);
    // render_mini_map(data);
    mlx_put_image_to_window(data->mlx->init, data->mlx->win, data->new_image.img, 0, 0);
    l++;
	// free_old_rays(data->rays);
    return (0);
    // render_static_map(data);
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
    t_img new_image;
char *map[] = {
    "11111111111111111111111111",
    "10000010011100001000000001",
    "10100011110101111111111001",
    "10100000000000000000001001",
    "10100000010000101111101001",
    "10101000010000000000101001",
    "10101010111111111110101001",
    "10101000010000000000101001",
    "10101111110010001110100111",
    "10100000000000000000001001",
    "10111111111111111111111001",
    "10000000000000000000000001",
    "11111111111111111111111111",
    "11111111111111111111111111",
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