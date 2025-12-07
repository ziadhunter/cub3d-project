#include <cub3d.h>

static int is_position_wall(t_data *data, double x, double y)
{
	double map_x = x / TILE_SIZE;
	double map_y = y / TILE_SIZE;
	
	if (map_x < 0 || map_y < 0 || map_x >= data->map_info->map_width || map_y >= data->map_info->map_height)
		return (1);
	
	return (data->map[(int)map_y][(int)map_x].cell_type == WALL ||
			(data->map[(int)map_y][(int)map_x].cell_type == DOOR &&
				((t_door *)(data->map[(int)map_y][(int)map_x].options))->door_state >= CLOSED));
}

static int check_collision(t_data *data, double x, double y)
{
	double buffer = 10.0;
	if (is_position_wall(data, x, y))
		return (1);
	// // Check 4 diagonal corners
	if (is_position_wall(data, x - buffer, y - buffer) ||
		is_position_wall(data, x + buffer, y - buffer) ||
		is_position_wall(data, x - buffer, y + buffer) ||
		is_position_wall(data, x + buffer, y + buffer))
		return (1);
	
	return (0);
}

void	update_palyer_state(t_data *data, t_player *player)
{
	double	x;
	double	y;

	x = player->x;
	y = player->y;
	x += ((cos(player->rotation_angle) * player->walking_speed / 3)
			* player->walk_direction.now);
	y += ((sin(player->rotation_angle) * player->walking_speed / 3)
			* player->walk_direction.now);
	x += ((cos(player->rotation_angle + PI / 2) * player->walking_speed / 3)
			* player->side_direction.now);
	y += ((sin(player->rotation_angle + PI / 2) * player->walking_speed / 3)
			* player->side_direction.now);

	// if (is_wall(data, &x, &y))
	// {
	// 	player->x = x;
	// 	player->y = y;
	// }

	if (!check_collision(data, x, player->y))
		player->x = x;
	if (!check_collision(data, player->x, y))
		player->y = y;

	data->player->rotation_angle += (data->player->rotation_speed
			* data->player->rotation_direction.now);
}