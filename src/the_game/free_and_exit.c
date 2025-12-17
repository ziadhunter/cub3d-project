/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:13:38 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/15 12:10:55 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_rays(t_ray **rays)
{
	int	i;

	i = 0;
	while (i < NUM_COLUMNS)
		free(rays[i++]);
	free(rays);
}

void	delete_texture(void *mlx_ptr, void *img)
{
	if (img)
		mlx_destroy_image(mlx_ptr, img);
}

void	destroy_textures(t_data *data, t_texture *textures, t_player *player)
{
	delete_texture(data->mlx->init, textures->door.img);
	delete_texture(data->mlx->init, textures->close_door_btn.img);
	delete_texture(data->mlx->init, textures->open_door_btn.img);
	delete_texture(data->mlx->init, textures->door_inside.img);
	delete_texture(data->mlx->init, textures->ea.img);
	delete_texture(data->mlx->init, textures->we.img);
	delete_texture(data->mlx->init, textures->so.img);
	delete_texture(data->mlx->init, textures->no.img);
	delete_texture(data->mlx->init, player->knife.knife_attack.img);
	delete_texture(data->mlx->init, player->knife.knife_move.img);
}

void	free_cells_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map == NULL)
		return ;
	while (i < data->map_info->rows)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	clear_dlist(&(data->doors_list));
}

void	free_all_data_and_exit(t_data *data, char *str, int exit_status)
{
	destroy_textures(data, &data->textures, data->player);
	mlx_destroy_image(data->mlx->init, data->new_image.img);
	mlx_destroy_window(data->mlx->init, data->mlx->win);
	mlx_destroy_display(data->mlx->init);
	free(data->mlx->init);
	free(data->mlx);
	free(data->player);
	free_rays(data->rays);
	free_cells_map(data);
	free_map(data->map_info);
	free(data);
	if (str)
		printf("%s", str);
	exit(exit_status);
}
