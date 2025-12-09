#include <cub3d.h>

#define DOOR_CHECK_RANGE 96

int is_dwall(t_data *data, t_ray_info *ray_info, t_direction *intr)
{
	int rx = (int)(ray_info->x_intr / TILE_SIZE);
	int ry = (int)(ray_info->y_intr / TILE_SIZE);

	if (data->map[ry][rx].cell_type == WALL || data->map[ry][rx].cell_type == DOOR)
    {
        intr->x = ray_info->x_intr;
        intr->y = ray_info->y_intr;
        return (1);
    }
	return (0);
}

double find_hy_intersection(t_data *data)
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

double find_vx_intersection(t_data *data)
{
    return (floor(data->player->x / TILE_SIZE) * TILE_SIZE);
}

void find_v_inter(t_data *data, t_ray *ray, t_direction *v_intr)
{
	t_ray_info ray_info;

	if (fabs(cos(ray->ray_angle)) < VERTICAL_RAY_THRESHOLD)
		return ;

    ray_info.x_step = TILE_SIZE;
    ray_info.y_step = (TILE_SIZE * tan(ray->ray_angle));

    ray_info.x_intr = find_vx_intersection(data);

    if (ray->ray_direction.x > 0)
        ray_info.x_intr += TILE_SIZE;

        
    ray_info.y_intr = find_vy_intersection(data, ray, ray_info.x_intr);
    if (ray->ray_direction.x < 0)
        ray_info.x_step *= -1;

    if (ray->ray_direction.x < 0)
        ray_info.x_intr--;
    if ((ray->ray_direction.y > 0 && ray_info.y_step > 0) || (ray->ray_direction.x < 0 && ray_info.y_step < 0))
        ray_info.y_step *= -1;

    while ((ray_info.x_intr >= 0 && ray_info.x_intr < data->map_info->map_width)
        && (ray_info.y_intr >= 0 && ray_info.y_intr < data->map_info->map_height))
    {
        if (is_dwall(data, &ray_info, v_intr))
            break;
        ray_info.x_intr += ray_info.x_step;
        ray_info.y_intr += ray_info.y_step;
    }
}

void find_h_inter(t_data *data, t_ray *ray, t_direction *h_intr)
{
	t_ray_info ray_info;

	if (fabs(tan(ray->ray_angle)) < VERTICAL_RAY_THRESHOLD)
		return ;
    ray_info.y_step = TILE_SIZE;
    ray_info.x_step = (TILE_SIZE / tan(ray->ray_angle));
    ray_info.y_intr = find_hy_intersection(data);
    if (ray->ray_direction.y < 0)
        ray_info.y_intr += TILE_SIZE;
    ray_info.x_intr = find_hx_intersection(data, ray, ray_info.y_intr);
    if (ray->ray_direction.y > 0)
        ray_info.y_step *= -1;
    if ((ray->ray_direction.x < 0 && ray_info.x_step > 0) || (ray->ray_direction.x > 0 && ray_info.x_step < 0))
        ray_info.x_step *= -1;
    if (ray->ray_direction.y > 0)
        ray_info.y_intr--;
    while ((ray_info.x_intr >= 0 && ray_info.x_intr < data->map_info->map_width)
        && (ray_info.y_intr >= 0 && ray_info.y_intr < data->map_info->map_height))
    {
        if (is_dwall(data, &ray_info, h_intr))
            break;
        ray_info.x_intr += ray_info.x_step;
        ray_info.y_intr += ray_info.y_step;
    }
}

double check_door_intersection(t_data *data, t_ray *s_ray)
{
    t_direction h_inter, v_inter;
    double h_dist, v_dist;

    h_inter.x = 10000000000.0;
    h_inter.y = 10000000000.0;
    v_inter.x = 10000000000.0;
    v_inter.y = 10000000000.0;
    facing_direction(s_ray->ray_angle, s_ray);
    find_h_inter(data, s_ray, &h_inter);
    find_v_inter(data, s_ray, &v_inter);
    h_dist = hypot(s_ray->start_x - h_inter.x, s_ray->start_y - h_inter.y);
    v_dist = hypot(s_ray->start_x - v_inter.x, s_ray->start_y - v_inter.y);
    if (h_dist < v_dist)
    {
        s_ray->end_x = h_inter.x;
        s_ray->end_y = h_inter.y;
        return (h_dist);
    }
    else
    {
        s_ray->end_x = v_inter.x;
        s_ray->end_y = v_inter.y;
        return (v_dist);
    }

}

bool check_door(int x, int y, double final_dist, t_data *data)
{
    t_cell *cell;

    cell = &(data->map[y / TILE_SIZE][x / TILE_SIZE]);
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

void	render_mini_map_rays(t_data *data, t_cord cord, double z, double w);

void door_check_using_rays(t_data *data)
{
    t_ray mid_ray = {.start_x = data->player->x, .start_y = data->player->y, .ray_angle = data->player->rotation_angle};
    double final_dist;
    double x = X_START_POINT + (MAP_SIZE / 2), x_end;
    double y = Y_START_POINT + (MAP_SIZE / 2), y_end;

    // data->player->is_looking_at_door = false;
    final_dist = check_door_intersection(data, &mid_ray);
    printf("%f\n", final_dist);
    // data->player->is_looking_at_door = check_door(mid_ray.end_x, mid_ray.end_y, final_dist, data);
    data->player->is_looking_at_door = false;
    y_end = y + ((mid_ray.end_y - data->player->y) / MINIMAP_SCALE);
    x_end = x + ((mid_ray.end_x - data->player->x) / MINIMAP_SCALE);
    render_mini_map_rays(data, (t_cord){x, y}, x_end, y_end);
}

void update_door_state(t_data *data)
{
    t_door *door;
    door = data->player->door;
    if (door == NULL)
        return ;
    if (door->door_state <= OPENED)
        door->door_state = CLOSING;
    else if (door->door_state >= CLOSED)
        door->door_state = OPENING;
}