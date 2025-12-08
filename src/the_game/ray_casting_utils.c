/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:38:43 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/08 01:55:03 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

void	facing_direction(double ray_angle, t_ray *ray)
{
	ray->ray_direction.y = 1;
	ray->ray_direction.x = 1;
	if (ray_angle > 0 && ray_angle < PI)
		ray->ray_direction.y = -1;
	if (ray_angle > 0.5 * PI && ray_angle < 1.5 * PI)
		ray->ray_direction.x = -1;
}


int is_door(t_data *data, double x, double y, double offset)
{
	t_cell *cell;
	t_door *door;
	int rx = (int)(x / TILE_SIZE);
	int ry = (int)(y / TILE_SIZE);

	if (!(x >= 0 && x < data->map_info->map_width
		&& y >= 0 && y < data->map_info->map_height))
		return (NONE);
	cell = &(data->map[ry][rx]);
	if (cell->cell_type == DOOR)
	{
		door = (t_door *)(cell->options);
		if (door->is_valid == false)
			return (NONE);
		if (((int)(offset) % TILE_SIZE) < door->door_position) 
			return (DOOR);
	}
	return (NONE);
}

int	wall(t_data *data, double x, double y)
{
	t_cell *cell;
	t_door *door;
	double rx = x / TILE_SIZE;
	double ry = y / TILE_SIZE;

	cell = &(data->map[(int)ry][(int)rx]);
	if (cell->cell_type == WALL)
		return (WALL);
	else if (cell->cell_type == DOOR)
	{
		door = cell->options;
		if (door->is_valid == false)
			return (WALL);
		return (DOOR);
	}

	return (NONE);
}

void	insert_end_ray(t_ray *ray, t_direction *dir, int intersection)
{
	ray->end_x = dir->x;
	ray->end_y = dir->y;
	ray->intersection = intersection;
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
