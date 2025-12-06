/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projaction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:46:07 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/02 14:37:05 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

void	render_wall(t_data *data, int x, int y, int wall_hight)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = y + wall_hight;
	while (i < y)
	{
		put_pixel(&data->new_image, x, i, WHITE);
		i++;
	}
	while (i < tmp)
	{
		put_pixel(&data->new_image, x, i, BLUE);
		i++;
	}
	while (i < WIN_HEIGHT)
	{
		put_pixel(&data->new_image, x, i, BLACK);
		i++;
	}
}

void	projaction(t_data *data)
{
	int		i;
	double	ray_distance;
	double	distance_projaction_plane;
	double	wall_hight;
	t_ray	*ray;

	i = 0;
	distance_projaction_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < NUM_COLUMNS)
	{
		ray = data->rays[i];
		ray_distance = hypot(ray->end_x - ray->start_x, ray->end_y
				- ray->start_y);
		ray_distance = cos(ray->ray_angle - data->player->rotation_angle)
			* ray_distance;
		wall_hight = (TILE_SIZE / ray_distance) * distance_projaction_plane;
		if (wall_hight > WIN_HEIGHT)
			wall_hight = WIN_HEIGHT;
		render_wall(data, i, (WIN_HEIGHT / 2) - ((int)wall_hight / 2),
			(int)wall_hight);
		i++;
	}
}
