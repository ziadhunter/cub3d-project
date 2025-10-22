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
				x_map = ((data->player->x + ((x - CENTER_MAP_X) * MINIMAP_SCALE))) / TILE_SIZE;
                y_map = ((data->player->y + ((y - CENTER_MAP_Y) * MINIMAP_SCALE))) / TILE_SIZE;
                color = WHITE;
                if (y_map >= 0 && y_map < MAP_HEIGHT &&
                    x_map >= 0 && x_map < MAP_WIDTH)
                    if (data->map[y_map][x_map] == '1')
                        color = BLACK;
                put_pixel(&data->new_image, x, y, color);
            }
            x++;
        }
        y++;
    }
}

void render_player_mini_map(t_data *data)
{
    int cx = X_START_POINT + (MAP_SIZE / 2);
    int cy = Y_START_POINT + (MAP_SIZE / 2);
    int x = cx - data->player->radius;
    int y = cy - data->player->radius;
    int r = data->player->radius;

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
}

void render_mini_map_rays(t_data *data, double x, double y, double z, double w)
{
    double xi;
    double yi;
    double dx;
    double dy;
    int step;

    if (fabs(z - x) > fabs(w - y))
        step = fabs(z - x);
    else
        step = fabs(w - y);
    xi = (z - x) / step;
    yi = (w - y) / step;
    for (int i = 0; i < step; i++)
    {
        dx = x - CENTER_MAP_X;
        dy = y - CENTER_MAP_Y;
        if (sqrt(dx * dx + dy * dy) > MAP_RADIUS)
            break;

        //can u add a condtion to stop rendring this line when it get out of the mini map raduis
        put_pixel(&data->new_image, x, y, BLUE);
        x += xi;
        y += yi;
    }
}

void render_rays_mini_map(t_data *data)
{
	double x = X_START_POINT + (MAP_SIZE / 2);
    double y = Y_START_POINT + (MAP_SIZE / 2);
	double y_end;
	double x_end;
	int i = 0;

	while (i < NUM_COLUMNS)
	{
		y_end = y + ((data->rays[i]->end_y - data->player->y) / MINIMAP_SCALE);
		x_end = x + ((data->rays[i]->end_x - data->player->x) / MINIMAP_SCALE);
		render_mini_map_rays(data, x, y, x_end, y_end);
		i++;
	}
}

void render_mini_map(t_data *data)
{
    base_of_mini_map(data);
    mini_map(data);
	render_rays_mini_map(data);
    render_player_mini_map(data);
}