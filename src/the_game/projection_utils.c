/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:59:22 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/13 22:05:11 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_info_about_door(t_data *data, t_ray *ray, t_direction ray_s)
{
	t_door	*door;

	door = (t_door *)(data->map[(int)((ray->end_y - ray_s.y)
				/ TILE_SIZE)][(int)((ray->end_x - ray_s.x)
				/ TILE_SIZE)].options);
	if (door->is_valid)
		ray->hit_cell = &data->textures.door;
	else
		ray->hit_cell = &data->textures.door_inside;
	if (ray->intersection == HORIZONTAL)
		ray->x_offset = ray->end_x % TILE_SIZE + (TILE_SIZE
				- door->door_position);
	else if (ray->intersection == VERTICAL)
		ray->x_offset = ray->end_y % TILE_SIZE + (TILE_SIZE
				- door->door_position);
}

void	get_info_about_hwall(t_data *data, t_ray *ray, t_direction ray_s)
{
	ray->x_offset = ray->end_x % TILE_SIZE;
	if (ray->ray_direction.y < 0)
	{
		if (data->map[(int)((ray->end_y - 2) / TILE_SIZE)][(int)(ray->end_x
				/ TILE_SIZE)].cell_type == DOOR)
			ray->hit_cell = &data->textures.door_inside;
		else
			ray->hit_cell = &data->textures.so;
		ray->x_offset = (TILE_SIZE - 1) - ray->x_offset;
	}
	else
	{
		if (data->map[(int)((ray->end_y + 2) / TILE_SIZE)][(int)(ray->end_x
				/ TILE_SIZE)].cell_type == DOOR)
			ray->hit_cell = &data->textures.door_inside;
		else
			ray->hit_cell = &data->textures.no;
	}
}

void	get_info_about_vwall(t_data *data, t_ray *ray, t_direction ray_s)
{
	ray->x_offset = ray->end_y % TILE_SIZE;
	if (ray->ray_direction.x > 0)
	{
		if (data->map[(int)(ray->end_y / TILE_SIZE)][(int)((ray->end_x - 2)
				/ TILE_SIZE)].cell_type == DOOR)
			ray->hit_cell = &data->textures.door_inside;
		else
			ray->hit_cell = &data->textures.ea;
	}
	else
	{
		if (data->map[(int)(ray->end_y / TILE_SIZE)][(int)((ray->end_x + 2)
				/ TILE_SIZE)].cell_type == DOOR)
			ray->hit_cell = &data->textures.door_inside;
		else
			ray->hit_cell = &data->textures.we;
		ray->x_offset = (TILE_SIZE - 1) - ray->x_offset;
	}
}

void	get_info_about_target_cell(t_data *data, t_ray *ray)
{
	t_direction	ray_s;

	ray_s.x = 0;
	ray_s.y = 0;
	if (ray->intersection == VERTICAL && ray_facing_left(ray->ray_direction))
		ray_s.x++;
	if (ray->intersection == HORIZONTAL && ray_facing_up(ray->ray_direction))
		ray_s.y++;
	if (data->map[(int)((ray->end_y - ray_s.y) / TILE_SIZE)][(int)((ray->end_x
				- ray_s.x) / TILE_SIZE)].cell_type == DOOR)
		get_info_about_door(data, ray, ray_s);
	else if (ray->intersection == HORIZONTAL)
		get_info_about_door(data, ray, ray_s);
	else
		get_info_about_vwall(data, ray, ray_s);
}
