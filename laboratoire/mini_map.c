#include "cub.h"

void base_of_mini_map(t_data *data)
{
    int y = Y_START_POINT - 3;
    int x = X_START_POINT - 3;
    while (y < MAP_SIZE + Y_START_POINT + 3)
    {
        x = X_START_POINT - 3;
        while (x < MAP_SIZE + X_START_POINT + 3)
        {
            if (((x - CENTER_MAP_X) * (x - CENTER_MAP_X) + (y - CENTER_MAP_Y) * (y - CENTER_MAP_Y)) <= ((MAP_RADIUS + 3) * (MAP_RADIUS + 3)))
                put_pixel(&data->new_image, x, y, WHITE);
            x++;
        }
        y++;
    }
}

void mini_map(t_data *data)
{
    int y = Y_START_POINT;
    int x;
    int x_map, y_map;
    int color;

    while (y < Y_START_POINT + MAP_SIZE)
    {
        x = X_START_POINT;
        while (x < X_START_POINT + MAP_SIZE)
        {
            if (((x - CENTER_MAP_X) * (x - CENTER_MAP_X) +
                 (y - CENTER_MAP_Y) * (y - CENTER_MAP_Y)) <= (MAP_RADIUS * MAP_RADIUS))
            {
				x_map = ((data->player->x - ((x - CENTER_MAP_X) * MINIMAP_SCALE))) / TILE_SIZE;
				y_map = ((data->player->y - ((y - CENTER_MAP_Y) * MINIMAP_SCALE))) / TILE_SIZE;
                color = BLACK;
                if (y_map >= 0 && y_map < MAP_WIDTH &&
                    x_map >= 0 && x_map < MAP_LENGTH)
                    if (data->map[y_map][x_map] == '0')
                        color = WHITE;
                put_pixel(&data->new_image, x, y, color);
            }
            x++;
        }
        y++;
    }
}

void render_mini_map(t_data *data)
{
    base_of_mini_map(data);
    mini_map(data);
	render_rays_mini_map(data);
    render_player_mini_map(data);
}