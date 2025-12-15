/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:28:15 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/14 21:30:02 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	load_xpm(t_data *data, char *path, t_img *img)
{
	if (path == NULL)
		return ;
	
	if (!file_isvalid(path))
		free_all_data_and_exit(data, NULL, 1);
	img->img = mlx_xpm_file_to_image(data->mlx->init, path, &(img->width),
			&(img->height));
	if (img->img == NULL)
	{
		perror("mlx_xpm_file_to_image: ");
		return ;
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
			&img->endian);
}

/* TODO: check if file exist first */
void	load_textures(t_data *data)
{
	load_xpm(data, data->map_info->no, &(data->textures.no));
	load_xpm(data, data->map_info->so, &(data->textures.so));
	load_xpm(data, data->map_info->we, &(data->textures.we));
	load_xpm(data, data->map_info->ea, &(data->textures.ea));
	load_xpm(data, "textures/door.xpm", &(data->textures.door));
	load_xpm(data, "textures/door_in.xpm", &(data->textures.door_inside));
	load_xpm(data, "textures/close_door_btn.xpm",
		&(data->textures.close_door_btn));
	load_xpm(data, "textures/open_door_btn.xpm",
		&(data->textures.open_door_btn));
}

void	load_colors(t_data *data)
{
	data->textures.floor_color = (data->map_info->f[0] << 16)
		| (data->map_info->f[1] << 8) | data->map_info->f[2];
	data->textures.ceil_color = (data->map_info->c[0] << 16)
		| (data->map_info->c[1] << 8) | data->map_info->c[2];
}

void	load_game_data(t_data *data)
{
	load_textures(data);
	load_weapons(data);
	load_colors(data);
}
