/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projaction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:46:07 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/01 17:47:08 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	render_wall(t_data *data, int x, int y, int wall_hight)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = y + wall_hight;
	// printf("wall h: %d\n", wall_hight);
	// printf("w: %d\n", y);
	while (i < y)
	{
		put_pixel(&data->new_image, x, i, WHITE);
		i++;
	}
	// printf("b: %d\n", tmp);
	while (i < tmp)
	{
		put_pixel(&data->new_image, x, i, BLUE);
		i++;
	}
	// printf("d: %d\n", WIN_HEIGHT);
	while (i < WIN_HEIGHT)
	{
		put_pixel(&data->new_image, x, i, BLACK);
		i++;
	}
}

void	projaction(t_data *data)
{
	int i = 0;
	double ray_distance;
	double distanceProjactionPlane;
	double wall_hight;
	t_ray *ray;
	distanceProjactionPlane = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < NUM_COLUMNS)
	{
		ray = data->rays[i];
		ray_distance = hypot(ray->end_x - ray->start_x, ray->end_y
				- ray->start_y);
		ray_distance = cos(ray->ray_angle - data->player->rotation_angle)
			* ray_distance;
		wall_hight = (TILE_SIZE / ray_distance) * distanceProjactionPlane;
		if (wall_hight > WIN_HEIGHT)
			wall_hight = WIN_HEIGHT;
		render_wall(data, i, (WIN_HEIGHT / 2) - ((int)wall_hight / 2),
				(int)wall_hight);
		i++;
	}
}