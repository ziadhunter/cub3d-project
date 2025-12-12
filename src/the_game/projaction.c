/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projaction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:46:07 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/10 01:42:31 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

int get_color(t_img *wall, int x, int y)
{
	return (*(unsigned int *)(wall->addr + (y * wall->line_length + x
						* (wall->bpp / 8))));
}

int distance_from_top(int i, int wall_hight)
{
	return (i + (wall_hight / 2) - (WIN_HEIGHT / 2));
}

void	render_column(t_data *data, int x, int y, int wall_hight)
{
	int	i;
	int	tmp;
	t_ray *ray;

	i = 0;
	tmp = y + wall_hight;
	if (tmp > WIN_HEIGHT)
		tmp = WIN_HEIGHT;
	ray = data->rays[x];
	while (i < y)
		put_pixel(&data->new_image, x, i++, *data->map_info->c);
	get_info_about_target_cell(data, ray);
	while (i < tmp)
	{
			ray->y_offset = distance_from_top(i, wall_hight) * ((float)TILE_SIZE / wall_hight);
			put_pixel(&data->new_image, x, i, get_color(ray->hit_cell, ray->x_offset, ray->y_offset));
		i++;
	}
	while (i < WIN_HEIGHT)
		put_pixel(&data->new_image, x, i++, *data->map_info->f);
}

void diplay_btn_msg(t_data *data)
{
    int x, y;
    int i, j;
    unsigned int color;
    t_img *door_btn;

    x = (WIN_WIDTH / 2) - (120 / 2);
    y = (WIN_HEIGHT / 4) - (39 / 2);
    if (data->player->door->door_state <= OPENED)
        door_btn = &(data->textures.close_door_btn);
    else
        door_btn = &(data->textures.open_door_btn);
    j = 0;
    while (j < door_btn->height)
    {
        i = 0;
        while (i < door_btn->width)
        {
            color = get_color(door_btn, i, j);
            if (color != 0xFF000000)
                put_pixel(&data->new_image, x + i, y + j, color);
            i++;
        }
        j++;
    }
}

void	projaction(t_data *data)
{
	int		i;
	double	ray_distance;
	double	distance_projaction_plane;
	double	wall_hight;
	t_ray	*ray;

	i = 0;
	distance_projaction_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < NUM_COLUMNS)
	{
		ray = data->rays[i];
		ray_distance = hypot(ray->end_x - ray->start_x, ray->end_y
				- ray->start_y);
		ray_distance = cos(ray->ray_angle - data->player->rotation_angle)
			* ray_distance;
		wall_hight = (TILE_SIZE / ray_distance) * distance_projaction_plane;
		render_column(data, i, (WIN_HEIGHT / 2) - ((int)wall_hight / 2),
			(int)wall_hight);
		i++;
	}
	// UNCOMMENT: after implementing open/close button
	if (data->player->is_looking_at_door == true)
	    diplay_btn_msg(data);
}
