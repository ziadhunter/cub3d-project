/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:01:00 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/03 16:30:51 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	short_ray(t_data *data, t_ray *ray, t_direction *horizontal_inters,
		t_direction *vertical_inters)
{
	double	dist_h;
	double	dist_v;

	if (horizontal_inters && vertical_inters)
	{
		dist_h = hypot(horizontal_inters->x - data->player->x,
				horizontal_inters->y - data->player->y);
		dist_v = hypot(vertical_inters->x - data->player->x,
				vertical_inters->y - data->player->y);
		if (dist_h < dist_v)
			insert_end_ray(ray, horizontal_inters);
		else
			insert_end_ray(ray, vertical_inters);
	}
	else if (horizontal_inters)
		insert_end_ray(ray, horizontal_inters);
	else if (vertical_inters)
		insert_end_ray(ray, vertical_inters);
}

void	find_horizontal_intersiction(
	t_data *data, double ray_angle, t_facing facing, t_direction *horz_inter)
{
	double	x_step;
	double	y_step;
	double	x_intr;
	double	y_intr;

	if (fabs(tan(ray_angle)) < 1e-6)
		return ;
	y_intr = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (!facing.facing_up)
		y_intr += TILE_SIZE;
	x_intr = ((y_intr - data->player->y) / tan(ray_angle)) + data->player->x;
	y_step = TILE_SIZE;
	if (facing.facing_up)
		y_step *= -1;
	x_step = TILE_SIZE / tan(ray_angle);
	if ((x_step > 0 && !facing.facing_right) || (x_step < 0
			&& facing.facing_right))
		x_step *= -1;
	if (facing.facing_up)
		y_intr--;
	while (x_intr >= 0 && x_intr < data->map_info->columns * TILE_SIZE
		&& y_intr >= 0 && y_intr < data->map_info->rows * TILE_SIZE)
	{
		if (wall(data, x_intr, y_intr))
		{
			horz_inter->x = x_intr;
			horz_inter->y = y_intr;
			return ;
		}
		x_intr += x_step;
		y_intr += y_step;
	}
}

void	find_vertical_intersiction(
	t_data *data, double ray_angle, t_facing facing, t_direction *vert_inter)
{
	double	x_step;
	double	y_step;
	double	x_intr;
	double	y_intr;

	if (fabs(cos(ray_angle)) < VERTICAL_RAY_THRESHOLD)
		return ;
	x_intr = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (facing.facing_right)
		x_intr += TILE_SIZE;
	y_intr = data->player->y + (x_intr - data->player->x) * tan(ray_angle);
	x_step = TILE_SIZE;
	if (!facing.facing_right)
		x_step *= -1;
	y_step = TILE_SIZE * tan(ray_angle);
	if ((y_step > 0 && facing.facing_up) || (y_step < 0 && !facing.facing_up))
		y_step *= -1;
	if (!facing.facing_right)
		x_intr--;
	while (x_intr >= 0 && x_intr < data->map_info->columns * TILE_SIZE
		&& y_intr >= 0 && y_intr < data->map_info->rows * TILE_SIZE)
	{
		if (wall(data, x_intr, y_intr))
		{
			vert_inter->x = x_intr;
			vert_inter->y = y_intr;
			return ;
		}
		x_intr += x_step;
		y_intr += y_step;
	}
}

void	define_ray_position(t_data *data, double ray_angle, t_ray *ray)
{
	t_facing	dir;
	t_direction	horizontal_inters;
	t_direction	vertical_inters;

	horizontal_inters.x = 0;
	horizontal_inters.y = 0;
	vertical_inters.x = 0;
	vertical_inters.y = 0;
	facing_direction(ray_angle, &dir);
	find_horizontal_intersiction(data, ray_angle, dir, &horizontal_inters);
	find_vertical_intersiction(data, ray_angle, dir, &vertical_inters);
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
