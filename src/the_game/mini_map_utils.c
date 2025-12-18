/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:58:28 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/19 00:37:05 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

void	base_of_mini_map(t_data *data)
{
	int	y;
	int	x;

	y = Y_START_POINT - 3;
	x = X_START_POINT - 3;
	while (y < data->map_s + Y_START_POINT + 3)
	{
		x = X_START_POINT - 3;
		while (x < data->map_s + X_START_POINT + 3)
		{
			if (((x - data->map_c.x) * (x - data->map_c.x) + (y - data->map_c.y)
					* (y - data->map_c.y)) <= ((data->map_r + 3) * (data->map_r
						+ 3)))
				put_pixel(&data->new_image, x, y, WHITE);
			x++;
		}
		y++;
	}
}

int	get_color_mini(t_data *data, char **map, int x, int y)
{
	int	color;

	color = WHITE;
	if (map[y][x] == '1' || (map[y][x] == 'D' && !door_is_valid(data, map, x,
				y)) || map[y][x] == 'O')
		color = BLACK;
	if (map[y][x] == 'D' && door_is_valid(data, map, x, y))
		color = BLUE;
	return (color);
}

void	mini_map(t_data *data, int x, int y, int color)
{
	int (x_map), (y_map);
	while (y < Y_START_POINT + data->map_s)
	{
		x = X_START_POINT;
		while (x < X_START_POINT + data->map_s)
		{
			if (((x - data->map_c.x) * (x - data->map_c.x) + (y - data->map_c.y)
					* (y - data->map_c.y)) <= (data->map_r * data->map_r))
			{
				x_map = ((data->player->x + ((x - data->map_c.x)
								* MINIMAP_SCALE))) / TILE_SIZE;
				y_map = ((data->player->y + ((y - data->map_c.y)
								* MINIMAP_SCALE))) / TILE_SIZE;
				if (y_map >= 0 && y_map < data->map_info->rows && x_map >= 0
					&& x_map < data->map_info->columns)
					color = get_color_mini(data, data->map_info->map, x_map,
							y_map);
				put_pixel(&data->new_image, x, y, color);
			}
			x++;
		}
		y++;
	}
}
