/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:49:58 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/19 00:37:05 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* TODO: error handling missing */

void	initialize_rays(t_data *data)
{
	int	i;

	i = 0;
	data->rays = malloc(sizeof(t_ray *) * NUM_COLUMNS);
	if (!data->rays)
		return ;
	while (i < NUM_COLUMNS)
	{
		data->rays[i] = malloc(sizeof(t_ray));
		if (!data->rays[i])
			return ;
		i++;
	}
}

void	initialization(t_data *data)
{
	initialize_rays(data);
	data->mlx = malloc(sizeof(t_mlx));
	data->mlx->init = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->init, WIN_WIDTH, WIN_HEIGHT,
			"3D game");
	mlx_mouse_hide(data->mlx->init, data->mlx->win);
	data->new_image.img = mlx_new_image(data->mlx->init, WIN_WIDTH, WIN_HEIGHT);
	data->new_image.addr = mlx_get_data_addr(data->new_image.img,
			&data->new_image.bpp,
			&data->new_image.line_length,
			&data->new_image.endian);
	data->map_info->map_height = data->map_info->rows * TILE_SIZE;
	data->map_info->map_width = data->map_info->columns * TILE_SIZE;
	data->player->is_looking_at_door = false;
	data->map_s = (WIN_HEIGHT / 3) - TILE_SIZE;
	data->map_r = data->map_s / 2;
	data->map_c.x = X_START_POINT + data->map_r;
	data->map_c.y = Y_START_POINT + data->map_r;
}
