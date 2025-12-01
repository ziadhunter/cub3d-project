/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:49:58 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/04 10:06:31 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	initialize_rays(t_data *data)
{
	data->rays = malloc(sizeof(t_ray *) * NUM_COLUMNS);
	if (!data->rays)
		return ;
	for (int i = 0; i < NUM_COLUMNS; i++)
	{
		data->rays[i] = malloc(sizeof(t_ray));
		if (!data->rays[i])
			return ;
	}
}

void	initialization(t_data *data)
{
	data->mlx = malloc(sizeof(t_mlx));
	data->mlx->init = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->init, WIN_WIDTH, WIN_HEIGHT,
			"3D game");
	data->new_image.img = mlx_new_image(data->mlx->init, WIN_WIDTH, WIN_HEIGHT);
	data->new_image.addr = mlx_get_data_addr(data->new_image.img,
												&data->new_image.bpp,
												&data->new_image.line_length,
												&data->new_image.endian);
	initialize_rays(data);
}