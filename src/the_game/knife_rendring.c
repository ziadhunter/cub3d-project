/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knife_rendring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:34:12 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/17 16:57:34 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	pick_pixel(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	put_image_to_window(t_img *dst, t_img *src, int x_src)
{
	int				y;
	int				x;
	unsigned int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = x_src;
		while (x < WIN_WIDTH + x_src)
		{
			color = pick_pixel(src, x, y);
			if (color != 0xFF000000 && color != 0x00FFFFFF)
				pput_pixel(dst, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_knife_attack(t_data *data)
{
	static int	i;

	put_image_to_window(&data->new_image, &data->player->knife.knife_attack,
		data->player->knife.knif_a_i * WIN_WIDTH);
	i++;
	if (i == 6)
	{
		i = 0;
		data->player->knife.knif_a_i++;
	}
	if (data->player->knife.knif_a_i == data->player->knife.knif_a_n - 1)
	{
		data->player->knife.knif_a_i = 0;
		data->player->knife.knife_state = 'N';
	}
}

void	render_knife_move(t_data *data)
{
	static int	i;
	static int	add = 1;

	put_image_to_window(&data->new_image, &data->player->knife.knife_move,
		data->player->knife.knif_m_i * WIN_WIDTH);
	i++;
	if (i == 7)
	{
		i = 0;
		data->player->knife.knif_m_i += add;
	}
	if (data->player->knife.knif_m_i == data->player->knife.knif_m_n - 1)
	{
		add = -1;
		data->player->knife.knife_state = 'N';
	}
	else if (data->player->knife.knif_m_i == 1)
	{
		add = 1;
		data->player->knife.knife_state = 'N';
	}
}

void	render_knife(t_data *data)
{
	if (data->player->knife.knife_state == 'H')
		render_knife_attack(data);
	else
		render_knife_move(data);
}
