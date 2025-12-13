#include <cub3d.h>

void	speed_adjustment(int keycode, t_data *data)
{
	if (keycode == SHIFT_SPEED)
		data->player->walking_speed += 2;
	if (keycode == SPEED_DOWN && data->player->walking_speed > MIN_WALK_SPEED)
		data->player->walking_speed -= 0.25;
	if (keycode == SPEED_UP && data->player->walking_speed < MAX_WALK_SPEED)
		data->player->walking_speed += 0.25;
	if (keycode == R_SPEED_DOWN
		&& data->player->rotation_speed > MIN_ROTATION_SPEED)
		data->player->rotation_speed -= 0.0015;
	if (keycode == R_SPEED_UP
		&& data->player->rotation_speed < MAX_ROTATION_SPEED)
		data->player->rotation_speed += 0.0015;
}