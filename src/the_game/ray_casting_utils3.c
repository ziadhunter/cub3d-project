/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:48:30 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/13 22:48:37 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	short_ray(t_data *data, t_ray *ray, t_direction *horizontal_inters,
		t_direction *vertical_inters)
{
	double	dist_h;
	double	dist_v;

	dist_h = hypot(horizontal_inters->x - data->player->x, horizontal_inters->y
			- data->player->y);
	dist_v = hypot(vertical_inters->x - data->player->x, vertical_inters->y
			- data->player->y);
	if (dist_h < dist_v - 1e-6)
		insert_end_ray(ray, horizontal_inters, HORIZONTAL);
	else
		insert_end_ray(ray, vertical_inters, VERTICAL);
}

static double	get_offset(t_ray_info ray_info, int intersection_type)
{
	if (intersection_type == VERTICAL)
		return (floor(ray_info.y_intr + ((ray_info.y_step / 2))));
	return (floor(ray_info.x_intr + ((ray_info.x_step / 2))));
}

static void	set_ray_end_cords(t_direction *inter, t_ray_info *ray_info,
	int cell_type)
{
	inter->y = ray_info->y_intr;
	inter->x = ray_info->x_intr;
	if (cell_type == DOOR)
	{
		inter->y += (ray_info->y_step / 2);
		inter->x += (ray_info->x_step / 2);
	}
}

bool	targeted_cell_not_empty(t_data *data, t_ray_info ray_info,
		t_direction *inter, int intersection_type)
{
	t_cell_type	cell_type;
	t_ray_info	check_info;
	double		offset;

	check_info = ray_info;
	if (intersection_type == HORIZONTAL
		&& ray_facing_up(check_info.ray_direction))
		check_info.y_intr--;
	else if (intersection_type == VERTICAL
		&& ray_facing_left(check_info.ray_direction))
		check_info.x_intr--;
	cell_type = wall(data, check_info.x_intr, check_info.y_intr);
	if (cell_type == DOOR)
	{
		offset = get_offset(check_info, intersection_type);
		cell_type = is_door(data, check_info.x_intr + ((check_info.x_step / 2)),
				check_info.y_intr + ((check_info.y_step / 2)), offset);
	}
	if (cell_type != NONE)
	{
		set_ray_end_cords(inter, &ray_info, cell_type);
		return (true);
	}
	return (false);
}
