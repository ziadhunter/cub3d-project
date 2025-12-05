/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:13:38 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/02 13:47:01 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_rays(t_ray **rays)
{
	int	i;

	i = 0;
	while (i < NUM_COLUMNS)
		free(rays[i++]);
	free(rays);
}

void	free_all_data_and_exit(t_data *data, char *str)
{
	mlx_destroy_image(data->mlx->init, data->new_image.img);
	free(data->mlx);
	free(data->player->old_move);
	free(data->player);
	free_rays(data->rays);
	free_map(data->map_info);
	free(data);
	printf("%s", str);
	exit(0);
}
