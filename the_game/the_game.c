/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:13:01 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/04 11:42:33 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int is_wall(t_data *data, double *x, double *y)
{
    double px = data->player->x / TILE_SIZE;
    double py = data->player->y / TILE_SIZE;
    double rx = *x / TILE_SIZE;
    double ry = *y / TILE_SIZE;

    if (data->map_info->map[(int)ry][(int)rx] != '1')
        return (1);
    else if (data->map_info->map[(int)ry][(int)px] != '1')
    {
        *x = data->player->x;
        return (1);
    }
    else if (data->map_info->map[(int)py][(int)rx] != '1')
    {
        *y = data->player->y;
        return (1);
    }
    return (0);
}

void put_pixel(t_img *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
        return;
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}


void update_palyer_state(t_data *data, t_player *player)
{
    double x = player->x;
    double y = player->y;

    //update the x and y position of the player
    //ma39altch 3la hadchi tat3awed tfahmo!!!!!!!!!!!!!
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

int wall(t_data *data, double x, double y)
{
    double rx = x / TILE_SIZE;
    double ry = y / TILE_SIZE;

    if (data->map_info->map[(int)ry][(int)rx] != '0')
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

    if (fabs(tan(ray_angle)) < 1e-6)
        return (NULL);
    dir = malloc(sizeof(t_direction));
    if (!dir)
        return (NULL);
    dir->x = 0;
    dir->y = 0;
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
    while (x_intr >= 0 && x_intr < data->map_info->columns * TILE_SIZE
        && y_intr >= 0 && y_intr < data->map_info->rows * TILE_SIZE)
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
    return (dir);
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
    dir->x = 0;
    dir->y = 0;
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
    while (x_intr >= 0 && x_intr < data->map_info->columns * TILE_SIZE
        && y_intr >= 0 && y_intr < data->map_info->rows * TILE_SIZE)
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
    return (dir);
}

void insert_end_ray(t_ray *ray, t_direction *dir)
{
	ray->end_x = dir->x;
	ray->end_y = dir->y;
}

void short_ray(t_data * data, t_ray *ray, t_direction *horizontal_inters, t_direction *vertical_inters)
{
	double dist_h;
	double dist_v;

	if (horizontal_inters && vertical_inters)
    {
        dist_h = hypot(horizontal_inters->x - data->player->x,
                horizontal_inters->y - data->player->y);
        dist_v = hypot(vertical_inters->x - data->player->x,
                vertical_inters->y - data->player->y);
        if (dist_h < dist_v)
            insert_end_ray(ray, horizontal_inters);
        else
            insert_end_ray(ray, vertical_inters);
    }
    else if (horizontal_inters)
        insert_end_ray(ray, horizontal_inters);
    else if (vertical_inters)
        insert_end_ray(ray, vertical_inters);
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
    if(dir)
        free(dir);
    if(horizontal_inters)
        free(horizontal_inters);
    if(vertical_inters)
        free(vertical_inters);
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return (angle);
}

void creat_ray_casting(t_data *data)
{
    double ray_angle;
    int column;
    
    column = 0;
    ray_angle = data->player->rotation_angle - (FOV / 2);
    while (column < NUM_COLUMNS)
    {
		if (ray_angle > 2 * PI || ray_angle < 0)
        	ray_angle = normalize_angle(ray_angle);
		data->rays[column]->ray_angle = ray_angle;
		data->rays[column]->start_x = data->player->x;
		data->rays[column]->start_y = data->player->y;
        define_ray_position(data, ray_angle, data->rays[column]);
        ray_angle += FOV / NUM_COLUMNS;
        column++;
    }
}
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
    distanceProjactionPlane = (WIN_WIDTH / 2) / tan(FOV/2);
    while (i < NUM_COLUMNS)
    {
        ray = data->rays[i];
        ray_distance = hypot(ray->end_x - ray->start_x, ray->end_y - ray->start_y);
        ray_distance = cos(ray->ray_angle - data->player->rotation_angle) * ray_distance;
        wall_hight = (TILE_SIZE / ray_distance) * distanceProjactionPlane;
        if (wall_hight > WIN_HEIGHT)
            wall_hight = WIN_HEIGHT;
        render_wall(data, i, (WIN_HEIGHT / 2) - ((int)wall_hight / 2), (int)wall_hight);
        i++;
    }
}

int the_animation(t_data *data)
{
    static unsigned int l = 0;
    int i;
    int j;

    i = 0;
    j = 0;
    update_palyer_state(data, data->player);
	creat_ray_casting(data);
    projaction(data);
    render_mini_map(data);
    mlx_put_image_to_window(data->mlx->init, data->mlx->win, data->new_image.img, 0, 0);
    l++;
    return (0);
}

void start_the_game(t_data *data)
{
    initialization(data);


	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);

	mlx_loop_hook(data->mlx->init, the_animation, data);
	mlx_loop(data->mlx->init);
}