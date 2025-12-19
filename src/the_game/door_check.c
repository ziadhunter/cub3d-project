/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:08:23 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/19 12:11:15 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	check_door_intersection(t_data *data, t_ray *s_ray)
{
	t_direction	h_inter;
	t_direction	v_inter;
	double		v_dist;
	double		h_dist;

	h_inter.x = 1e11;
	h_inter.y = 1e11;
	v_inter.x = 1e11;
	v_inter.y = 1e11;
	facing_direction(s_ray->ray_angle, s_ray);
	find_horizontal_intersiction(data, s_ray, &h_inter, is_dwall);
	find_vertical_intersiction(data, s_ray, &v_inter, is_dwall);
	h_dist = hypot(s_ray->start_x - h_inter.x, s_ray->start_y - h_inter.y);
	v_dist = hypot(s_ray->start_x - v_inter.x, s_ray->start_y - v_inter.y);
	if (h_dist < v_dist)
	{
		s_ray->end_x = h_inter.x;
		s_ray->end_y = h_inter.y;
		s_ray->intersection = HORIZONTAL;
		return (h_dist);
	}
	s_ray->end_x = v_inter.x;
	s_ray->end_y = v_inter.y;
	s_ray->intersection = VERTICAL;
	return (v_dist);
}

bool	check_door(t_ray mid_ray, double final_dist, t_data *data)
{
	t_cell	*cell;
	t_icord	player_cord;
	t_icord	ray_cord;

	if (mid_ray.intersection == VERTICAL
		&& ray_facing_left(mid_ray.ray_direction))
		mid_ray.end_x--;
	else if (mid_ray.intersection == HORIZONTAL
		&& ray_facing_up(mid_ray.ray_direction))
		mid_ray.end_y--;
	ray_cord.x = mid_ray.end_x / TILE_SIZE;
	ray_cord.y = mid_ray.end_y / TILE_SIZE;
	player_cord.x = (int)data->player->x / TILE_SIZE;
	player_cord.y = (int)data->player->y / TILE_SIZE;
	if (ray_cord.x == player_cord.x && ray_cord.y == player_cord.y)
		return (false);
	cell = &(data->map[ray_cord.y][ray_cord.x]);
	if (cell->cell_type == DOOR && ((((t_door *)(cell->options))->is_valid)
		&& (final_dist) < TILE_SIZE * 2) && final_dist > 10)
	{
		data->player->door = cell->options;
		return (true);
	}
	data->player->door = NULL;
	return (false);
}

void	door_check_using_rays(t_data *data)
{
	t_ray	mid_ray;
	double	final_dist;

	mid_ray.start_x = data->player->x;
	mid_ray.start_y = data->player->y;
	mid_ray.ray_angle = data->player->rotation_angle;
	final_dist = check_door_intersection(data, &mid_ray);
	data->player->is_looking_at_door = check_door(mid_ray, final_dist, data);
}
