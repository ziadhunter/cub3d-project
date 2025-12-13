/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:58:28 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/13 22:39:43 by rabounou         ###   ########.fr       */
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
	while (y < MAP_SIZE + Y_START_POINT + 3)
	{
		x = X_START_POINT - 3;
		while (x < MAP_SIZE + X_START_POINT + 3)
		{
			if (((x - CENTER_MAP_X) * (x - CENTER_MAP_X) + (y - CENTER_MAP_Y)
					* (y - CENTER_MAP_Y)) <= ((MAP_RADIUS + 3) * (MAP_RADIUS
						+ 3)))
				put_pixel(&data->new_image, x, y, WHITE);
			x++;
		}
		y++;
	}
}

void	mini_map(t_data *data, int x, int y, int color)
{
	int (x_map), (y_map);
	while (y < Y_START_POINT + MAP_SIZE)
	{
		x = X_START_POINT;
		while (x < X_START_POINT + MAP_SIZE)
		{
			if (((x - CENTER_MAP_X) * (x - CENTER_MAP_X) + (y - CENTER_MAP_Y)
					* (y - CENTER_MAP_Y)) <= (MAP_RADIUS * MAP_RADIUS))
			{
				x_map = ((data->player->x + ((x - CENTER_MAP_X)
								* MINIMAP_SCALE))) / TILE_SIZE;
				y_map = ((data->player->y + ((y - CENTER_MAP_Y)
								* MINIMAP_SCALE))) / TILE_SIZE;
				color = WHITE;
				if (y_map >= 0 && y_map < data->map_info->rows && x_map >= 0
					&& x_map < data->map_info->columns)
					if (data->map_info->map[y_map][x_map] == '1')
						color = BLACK;
				put_pixel(&data->new_image, x, y, color);
			}
			x++;
		}
		y++;
	}
}
