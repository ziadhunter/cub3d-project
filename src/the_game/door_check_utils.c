/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:11:10 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/13 22:11:11 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	find_hy_intersection(t_data *data)
{
	return (floor(data->player->y / TILE_SIZE) * TILE_SIZE);
}

double	find_hx_intersection(t_data *data, t_ray *ray, double y_inter)
{
	return ((y_inter - data->player->y) / tan(ray->ray_angle)
		+ data->player->x);
}

double	find_vy_intersection(t_data *data, t_ray *ray, double x_inter)
{
	return ((x_inter - data->player->x) * tan(ray->ray_angle)
		+ data->player->y);
}

double	find_vx_intersection(t_data *data)
{
	return (floor(data->player->x / TILE_SIZE) * TILE_SIZE);
}

int	is_dwall(t_data *data, t_ray_info ray_info, t_direction *intr,
		int intersection_type)
{
	t_ray_info	check_info;
	int			rx;
	int			ry;

	check_info = ray_info;
	if (intersection_type == HORIZONTAL
		&& ray_facing_up(check_info.ray_direction))
		check_info.y_intr--;
	else if (intersection_type == VERTICAL
		&& ray_facing_left(check_info.ray_direction))
		check_info.x_intr--;
	rx = ((int)check_info.x_intr / TILE_SIZE);
	ry = ((int)check_info.y_intr / TILE_SIZE);
	if (data->map[ry][rx].cell_type == WALL
		|| data->map[ry][rx].cell_type == DOOR)
	{
		intr->x = ray_info.x_intr;
		intr->y = ray_info.y_intr;
		return (true);
	}
	return (false);
}
