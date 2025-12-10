/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:01:00 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/09 20:11:59 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	short_ray(t_data *data, t_ray *ray, t_direction *horizontal_inters,
		t_direction *vertical_inters)
{
	double	dist_h;
	double	dist_v;

	dist_h = hypot(horizontal_inters->x - data->player->x,
			horizontal_inters->y - data->player->y);
	dist_v = hypot(vertical_inters->x - data->player->x,
			vertical_inters->y - data->player->y);
	if (dist_h < dist_v)
		insert_end_ray(ray, horizontal_inters, HORIZONTAL);
	else
		insert_end_ray(ray, vertical_inters, VERTICAL);
}


bool targeted_cell_not_empty(t_data *data,
		t_ray_info ray_info, t_direction *inter)
{
	t_cell_type cell_type;

	cell_type = wall(data, ray_info.x_intr, ray_info.y_intr);
	if (cell_type == DOOR)
		cell_type = is_door(
			data,
			ray_info.x_intr + ((ray_info.x_step / 2)),
			ray_info.y_intr + ((ray_info.y_step / 2)),
			floor(ray_info.y_intr + ((ray_info.y_step / 2))));
	if (cell_type != NONE)
	{
		inter->y = ray_info.y_intr;
		inter->x = ray_info.x_intr;
		if (cell_type == DOOR)
		{
			inter->y += (ray_info.y_step / 2);
			inter->x += (ray_info.x_step / 2);
		}
		return (true);
	}
	return (false);
}

void	find_horizontal_intersiction(
	t_data *data, double ray_angle, t_ray *ray, t_direction *horz_inter)
{
	t_ray_info ray_info;

	if (fabs(tan(ray_angle)) < VERTICAL_RAY_THRESHOLD)
		return ;
	ray_info.y_intr = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_direction.y < 0)
		ray_info.y_intr += TILE_SIZE;
	ray_info.x_intr = ((ray_info.y_intr - data->player->y) / tan(ray_angle)) + data->player->x;
	ray_info.y_step = TILE_SIZE;
	if (ray->ray_direction.y > 0)
		ray_info.y_step *= -1;
	ray_info.x_step = TILE_SIZE / tan(ray_angle);
	if ((ray_info.x_step > 0 && ray->ray_direction.x < 0) || (ray_info.x_step < 0
			&& ray->ray_direction.x > 0))
		ray_info.x_step *= -1;
	if (ray->ray_direction.y > 0)
		ray_info.y_intr--;
	while (ray_info.x_intr >= 0 && ray_info.x_intr < data->map_info->map_width
		&& ray_info.y_intr >= 0 && ray_info.y_intr < data->map_info->map_height)
	{
		if (targeted_cell_not_empty(data, ray_info, horz_inter))
			return ;
		ray_info.x_intr += ray_info.x_step;
		ray_info.y_intr += ray_info.y_step;
	}
}

void	find_vertical_intersiction(
	t_data *data, double ray_angle, t_ray *ray, t_direction *vert_inter)
{
	t_ray_info ray_info;

	if (fabs(cos(ray_angle)) < VERTICAL_RAY_THRESHOLD)
		return ;
	ray_info.x_intr = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_direction.x > 0)
		ray_info.x_intr += TILE_SIZE;
	ray_info.y_intr = data->player->y + (ray_info.x_intr - data->player->x) * tan(ray_angle);
	ray_info.x_step = TILE_SIZE;
	if (ray->ray_direction.x < 0)
		ray_info.x_step *= -1;
	ray_info.y_step = TILE_SIZE * tan(ray_angle);
	if ((ray_info.y_step > 0 && ray->ray_direction.y > 0) || (ray_info.y_step < 0 && ray->ray_direction.y < 0))
		ray_info.y_step *= -1;
	if (ray->ray_direction.x < 0)
		ray_info.x_intr--;
	while (ray_info.x_intr >= 0 && ray_info.x_intr < data->map_info->map_width
		&& ray_info.y_intr >= 0 && ray_info.y_intr < data->map_info->map_height)
	{
		if (targeted_cell_not_empty(data, ray_info, vert_inter))
			return ;
		ray_info.x_intr += ray_info.x_step;
		ray_info.y_intr += ray_info.y_step;
	}
}

void	define_ray_position(t_data *data, double ray_angle, t_ray *ray)
{
	// t_facing	dir;
	t_direction	horizontal_inters;
	t_direction	vertical_inters;

	horizontal_inters.x = 100000000000.0;
	horizontal_inters.y = 100000000000.0;
	vertical_inters.x = 100000000000.0;
	vertical_inters.y = 100000000000.0;
	facing_direction(ray_angle, ray);
	find_horizontal_intersiction(data, ray_angle, ray, &horizontal_inters);
	find_vertical_intersiction(data, ray_angle, ray, &vertical_inters);
	short_ray(data, ray, &horizontal_inters, &vertical_inters);
}

void	creat_ray_casting(t_data *data)
{
	double	ray_angle;
	int		column;

	column = 0;
	ray_angle = data->player->rotation_angle - (FOV / 2);
	while (column < NUM_COLUMNS)
	{
		if (ray_angle > 2 * PI || ray_angle < 0)
			ray_angle = normalize_angle(ray_angle);
		data->rays[column]->ray_angle = ray_angle;
		data->rays[column]->start_x = data->player->x;
		data->rays[column]->start_y = data->player->y;
		define_ray_position(data, ray_angle, data->rays[column]);
		ray_angle += FOV / NUM_COLUMNS;
		column++;
	}
}
