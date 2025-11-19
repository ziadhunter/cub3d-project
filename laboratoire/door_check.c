#include "cub.h"

#define DOOR_CHECK_RANGE 96

int is_wall(t_data *data, double x, double y)
{
	double rx = x / TILE_SIZE;
	double ry = y / TILE_SIZE;

	data->player->is_looking_at_door = false;
	// if (data->map.map[(int)ry][(int)rx].cell_type == DOOR)
	// 	data->player->is_looking_at_door = true;

	if (data->map.map[(int)ry][(int)rx].cell_type == WALL)
		return (1);
	else if (data->map.map[(int)ry][(int)rx].cell_type == DOOR)
		return (1);
	return (0);
}

double find_hy_intersection(t_data *data, t_ray *ray)
{
    return (floor(data->player->y / TILE_SIZE) * TILE_SIZE);
}

double find_hx_intersection(t_data *data, t_ray *ray, double y_inter)
{
    return ((y_inter - data->player->y) / tan(ray->ray_angle) + data->player->x);
}

double find_vy_intersection(t_data *data, t_ray *ray, double x_inter)
{
    return ((x_inter - data->player->x) * tan(ray->ray_angle) + data->player->y);
}

double find_vx_intersection(t_data *data, t_ray *ray)
{
    return (floor(data->player->x / TILE_SIZE) * TILE_SIZE);
}

t_direction *find_v_inter(t_data *data, t_ray *ray, int ray_facing_up, int ray_facing_right)
{
    t_direction *dir;
    double x_step, y_step;
    double x_inter, y_inter;

    dir = malloc(sizeof(t_direction));

    dir->x = -1;
    dir->y = -1;

	if (fabs(cos(ray->ray_angle)) < VERTICAL_RAY_THRESHOLD)
		return (dir);

    x_step = TILE_SIZE;
    y_step = (TILE_SIZE * tan(ray->ray_angle));

    x_inter = find_vx_intersection(data, ray);

    if (ray_facing_right)
        x_inter += TILE_SIZE;

        
    y_inter = find_vy_intersection(data, ray, x_inter);
    if (!ray_facing_right)
        x_step *= -1;

    if (!ray_facing_right)
        x_inter--;
    if ((ray_facing_up && y_step > 0) || (!ray_facing_up && y_step < 0))
        y_step *= -1;

    while ((x_inter >= 0 && x_inter < MAP_WIDTH * TILE_SIZE) && (y_inter >= 0 && y_inter < MAP_HEIGHT * TILE_SIZE))
    {
        if (is_wall(data, x_inter, y_inter))
        {
            dir->x = x_inter;
            dir->y = y_inter;
            break;
        }

        x_inter += x_step;
        y_inter += y_step;
    }

    return (dir);
}

t_direction *find_h_inter(t_data *data, t_ray *ray, int ray_facing_up, int ray_facing_right)
{
    t_direction *dir;
    double x_step, y_step;
    double x_inter, y_inter;

    dir = malloc(sizeof(t_direction));
    dir->x = -1;
    dir->y = -1;

	if (fabs(tan(ray->ray_angle)) < 1e-6)
		return (dir);

    y_step = TILE_SIZE;
    x_step = (TILE_SIZE / tan(ray->ray_angle));

    y_inter = find_hy_intersection(data, ray);

    if (!ray_facing_up)
        y_inter += TILE_SIZE;

    x_inter = find_hx_intersection(data, ray, y_inter);

    if (ray_facing_up)
        y_step *= -1;

    if ((!ray_facing_right && x_step > 0) || (ray_facing_right && x_step < 0))
        x_step *= -1;

    if (ray_facing_up)
        y_inter--;

    while ((x_inter >= 0 && x_inter < MAP_WIDTH * TILE_SIZE) && (y_inter >= 0 && y_inter < MAP_HEIGHT * TILE_SIZE))
    {
        if (is_wall(data, x_inter, y_inter))
        {
            dir->x = x_inter;
            dir->y = y_inter;
            break;
        }

        x_inter += x_step;
        y_inter += y_step;
    }

    return (dir);
}

double check_door_intersection(t_data *data, t_ray *s_ray)
{
    t_direction *h_inter, *v_inter, *small_inter;
    int ray_facing_up;
    int ray_facing_right;
    double h_dist, v_dist;

    ray_facing_up = s_ray->ray_angle < 2 * PI && s_ray->ray_angle > PI;
    ray_facing_right = (s_ray->ray_angle > (3 * PI / 2) || s_ray->ray_angle < (PI / 2));

    h_inter = find_h_inter(data, s_ray, ray_facing_up, ray_facing_right);
    v_inter = find_v_inter(data, s_ray, ray_facing_up, ray_facing_right);

    h_dist = hypot(s_ray->start_x - h_inter->x, s_ray->start_y - h_inter->y);
    v_dist = hypot(s_ray->start_x - v_inter->x, s_ray->start_y - v_inter->y);

    // if (h_inter->x == -1 || v_inter->x == -1)
    //     printf("h_inter: %f, v_inter: %f\n", h_inter->x, v_inter->x);
    if (h_inter->x == -1)
    {
        s_ray->end_x = v_inter->x;
        s_ray->end_y = v_inter->y;
        return (v_dist);
    }
    else if (v_inter->x == -1)
    {
        s_ray->end_x = h_inter->x;
        s_ray->end_y = h_inter->y;
        return (h_dist);
    }
    else if (h_dist < v_dist)
    {
        s_ray->end_x = h_inter->x;
        s_ray->end_y = h_inter->y;
        return (h_dist);
    }
    else
    {
        s_ray->end_x = v_inter->x;
        s_ray->end_y = v_inter->y;
        return (v_dist);
    }

}

bool check_door(int x, int y, double final_dist, t_data *data)
{
    t_cell *cell;

    cell = &(data->map.map[y / TILE_SIZE][x / TILE_SIZE]);
    if (cell->cell_type == DOOR
            && ((((t_door *)(cell->options))->is_valid)
            && final_dist < TILE_SIZE * 2))
    {
        data->player->door = cell->options;
        return (true);
    }
    data->player->door = NULL;
    return (false);
}

void door_check_using_rays(t_data *data)
{
    t_ray mid_ray = {.start_x = data->player->x, .start_y = data->player->y, .ray_angle = data->player->rotation_angle};
    double y_end, x_end, final_dist;
    double x = X_START_POINT + (MAP_SIZE / 2);
    double y = Y_START_POINT + (MAP_SIZE / 2);

    // mid_ray.end_x = cos(mid_ray.ray_angle) * DOOR_CHECK_RANGE + mid_ray.start_x;
    // mid_ray.end_y = sin(mid_ray.ray_angle) * DOOR_CHECK_RANGE + mid_ray.start_y;

    final_dist = check_door_intersection(data, &mid_ray);

    // printf("x: %d, y: %d\n", mid_ray.end_x, mid_ray.end_y);
    // printf("final dist: %f\n", final_dist);
    data->player->is_looking_at_door = check_door(mid_ray.end_x, mid_ray.end_y, final_dist, data);
    y_end = y + ((mid_ray.end_y - data->player->y) / MINIMAP_SCALE);
    x_end = x + ((mid_ray.end_x - data->player->x) / MINIMAP_SCALE);

    render_mini_map_rays(data, x, y, x_end, y_end);


    // render_mini_map_rays(data, mid_ray.start_x, mid_ray.start_y, mid_ray.end_x, mid_ray.end_y);
}