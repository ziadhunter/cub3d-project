/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:01:45 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/19 00:21:36 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

void	render_player_mini_map(t_data *data)
{
	int	cx;
	int	cy;
	int	x;
	int	y;
	int	r;

	cx = X_START_POINT + (data->game_data.map_size / 2);
	cy = Y_START_POINT + (data->game_data.map_size / 2);
	x = cx - data->player->radius;
	y = cy - data->player->radius;
	r = data->player->radius;
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

void	render_mini_map_rays(t_data *data, t_cord cord, double z, double w)
{
	double	xi;
	double	yi;
	int		step;
	int		i;

	i = 0;
	if (fabs(z - cord.x) > fabs(w - cord.y))
		step = fabs(z - cord.x);
	else
		step = fabs(w - cord.y);
	xi = (z - cord.x) / step;
	yi = (w - cord.y) / step;
	while (i < step)
	{
		if ((cord.x - data->game_data.map_center.x) * (cord.x - data->game_data.map_center.x) + (cord.y
				- data->game_data.map_center.y) * (cord.y - data->game_data.map_center.y) > pow(data->game_data.map_radius, 2))
			break ;
		put_pixel(&data->new_image, cord.x, cord.y, RED);
		cord.x += xi;
		cord.y += yi;
		i++;
	}
}

void	render_rays_mini_map(t_data *data, int i)
{
	double		x;
	double		y;
	double		y_end;
	double		x_end;

	x = X_START_POINT + (data->game_data.map_size / 2);
	y = Y_START_POINT + (data->game_data.map_size / 2);
	while (i < NUM_COLUMNS)
	{
		y_end = y + ((data->rays[i]->end_y - data->player->y) / MINIMAP_SCALE);
		x_end = x + ((data->rays[i]->end_x - data->player->x) / MINIMAP_SCALE);
		render_mini_map_rays(data, (t_cord){x, y}, x_end, y_end);
		i += 50;
	}
}

void	render_mini_map(t_data *data)
{
	base_of_mini_map(data);
	mini_map(data, X_START_POINT, Y_START_POINT, WHITE);
	render_rays_mini_map(data, 0);
	render_player_mini_map(data);
}
