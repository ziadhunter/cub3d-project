/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_rendring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:12:22 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/09 16:53:47 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_image_to_new_window(t_img *dst, t_img *src, int x_src)
{
	int				y;
	int				x;
	int				i;
	int				j;
	unsigned int	color;

	y = 0;
	j = 0;
	while (y < 64)
	{
		x = x_src;
		i = 0;
		while (x < 64 + x_src)
		{
			color = pick_pixel(src, x, y);
			if (color != 0xFF000000 && color != 0x00FFFFFF)
				put_pixel(dst, coord.x + i, coord.y + j, color);
			x++;
			i++;
		}
		j++;
		y++;
	}
}

render_gun_show(t_data *data)
{
    static int i = 0;

    while (i < 6)
    {
        put_image_to_new_window(&data->new_image, &data->player->gun->gun_show, i * WIN_WIDTH);
    }
}

void render_gun(t_data *data)
{
    if (data->player->gun->gun_state == 'S')
        render_gun_show();
}