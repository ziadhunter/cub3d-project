/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:49:58 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/02 17:22:54 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	initialize_rays(t_data *data)
{
	int	i;

	i = 0;
	data->rays = malloc(sizeof(t_ray *) * NUM_COLUMNS);
	// wa7ed exiit hna
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
	// handli error hnA
	initialize_rays(data);
	data->mlx = malloc(sizeof(t_mlx));
	data->mlx->init = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->init, WIN_WIDTH, WIN_HEIGHT,
			"3D game");
	data->new_image.img = mlx_new_image(data->mlx->init, WIN_WIDTH, WIN_HEIGHT);
	data->new_image.addr = mlx_get_data_addr(data->new_image.img,
			&data->new_image.bpp,
			&data->new_image.line_length,
			&data->new_image.endian);
}
