/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:38:43 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/03 16:29:46 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	facing_direction(double ray_angle, t_facing *facing)
{
	facing->facing_up = 1;
	if (ray_angle > 0 && ray_angle < PI)
		facing->facing_up = 0;
	facing->facing_right = 0;
	if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)
		facing->facing_right = 1;
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

void	render_rays(t_data *data, t_cord cord, double z, double w)
{
	double	xi;
	double	yi;
	int		step;
	int		i;

	if (fabs(z - cord.x) > fabs(w - cord.y))
		step = fabs(z - cord.x);
	else
		step = fabs(w - cord.y);
	xi = (z - cord.x) / step;
	yi = (w - cord.y) / step;
	i = 0;
	while (i < step)
	{
		put_pixel(&data->new_image, cord.x, cord.y, BLUE);
		put_pixel(&data->new_image, cord.x + 1, cord.y, BLUE);
		put_pixel(&data->new_image, cord.x, cord.y + 1, BLUE);
		put_pixel(&data->new_image, cord.x, cord.y - 1, BLUE);
		put_pixel(&data->new_image, cord.x - 1, cord.y, BLUE);
		cord.x += xi;
		cord.y += yi;
		i++;
	}
}
