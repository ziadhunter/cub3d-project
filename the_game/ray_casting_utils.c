/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:38:43 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/01 17:41:30 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_direction	*facing_direction(double ray_angle)
{
	t_direction	*dir;

	dir = malloc(sizeof(t_direction));
	if (!dir)
		return (NULL);
	dir->x = (ray_angle > 0 && ray_angle < PI) ? 0 : 1;
	dir->y = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI) ? 1 : 0;
	return (dir);
}

int	wall(t_data *data, double x, double y)
{
	double	rx;
	double	ry;

	rx = x / TILE_SIZE;
	ry = y / TILE_SIZE;
	if (data->map_info->map[(int)ry][(int)rx] != '0')
		return (1);
	return (0);
}

void	insert_end_ray(t_ray *ray, t_direction *dir)
{
	ray->end_x = dir->x;
	ray->end_y = dir->y;
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}