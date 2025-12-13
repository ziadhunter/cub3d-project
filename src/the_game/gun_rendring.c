/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_rendring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:12:22 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/13 22:58:30 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// modify this base on your need later
void	put_image_to_new_window(t_img *dst, t_img *src, int x_src)
{
	int				y;
	int				x;
	int				i;
	int				j;
	unsigned int	color;

	y = 0;
	j = 0;
	while (y < WIN_HEIGHT)
	{
		x = x_src;
		i = 0;
		while (x < 64 + x_src)
		{
			color = pick_pixel(src, x, y);
			if (color != 0xFF000000 && color != 0x00FFFFFF)
			// 3put_pixel(dst, coord.x + i, coord.y + j, color);
			{
				printf("hello\n");
			}
			x++;
			i++;
		}
		j++;
		y++;
	}
}

void	render_gun_show(t_data *data)
{
	put_image_to_new_window(&data->new_image, &data->player->gun.gun_show,
		data->player->gun.gs_i * WIN_WIDTH);
	data->player->gun.gs_i++;
	if (data->player->gun.gs_i == data->player->gun.gs_n)
	{
		data->player->gun.gs_i = 0;
		data->player->gun.gun_state = 'N';
	}
}

void	render_gun_fire(t_data *data)
{
	put_image_to_new_window(&data->new_image, &data->player->gun.gun_fire,
		data->player->gun.gf_i * WIN_WIDTH);
	data->player->gun.gf_i++;
	if (data->player->gun.gf_i == data->player->gun.gf_n)
	{
		data->player->gun.gun_state = 'N';
		data->player->gun.bullets_in_chamber--;
		data->player->gun.gf_i = 0;
	}
}

void	render_gun_reload(t_data *data)
{
	put_image_to_new_window(&data->new_image, &data->player->gun.gun_reload,
		data->player->gun.gr_i * WIN_WIDTH);
	data->player->gun.gr_i++;
	if (data->player->gun.gr_i == data->player->gun.gr_n)
	{
		data->player->gun.gun_state = 'N';
		data->player->gun.gr_i = 0;
		data->player->gun.bullets_in_chamber = data->player->gun.chambre_size;
	}
}

void	render_gun_move(t_data *data)
{
	put_image_to_new_window(&data->new_image, &data->player->gun.gun_move,
		data->player->gun.gm_i * WIN_WIDTH);
	data->player->gun.gm_i++;
	if (data->player->gun.gm_i == data->player->gun.gm_n)
		data->player->gun.gm_i = 0;
}

void	render_gun(t_data *data)
{
	if (data->player->gun.gun_state == 'S')
		render_gun_show(data);
	else if (data->player->gun.gun_state == 'F')
		render_gun_fire(data);
	else if (data->player->gun.gun_state == 'R')
		render_gun_reload(data);
	else
		render_gun_move(data);
}