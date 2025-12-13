/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:43:37 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/11 15:15:07 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void draw_cross_hair(t_data *data)
{
    int cx = WIN_WIDTH / 2;
    int cy = WIN_HEIGHT / 2;
    int size = 10;
    int i;

    i = -size;
    while (i <= size)
    {
        mlx_pixel_put(data->mlx->init, data->mlx->win, cx + i, cy, RED);
        mlx_pixel_put(data->mlx->init, data->mlx->win, cx, cy + i, RED);
        mlx_pixel_put(data->mlx->init, data->mlx->win, cx + i + 1, cy, RED);
        mlx_pixel_put(data->mlx->init, data->mlx->win, cx + i - 1, cy, RED);
        mlx_pixel_put(data->mlx->init, data->mlx->win, cx, cy + i + 1, RED);
        mlx_pixel_put(data->mlx->init, data->mlx->win, cx, cy + i - 1, RED);
        i++;
    }

}

int mouse_press(int key, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    if (key == 1)
    {
        if (data->player->gun_or_knife && data->player->gun.gun_state == 'N')
        {
            if (data->player->gun.bullets_in_chamber > 0) 
            data->player->gun.gun_state = 'F';
        }
        else if (!data->player->gun_or_knife && data->player->knife.knife_state == 'N')
            data->player->knife.knife_state = 'H';
    }
    return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	center_x;
	int	center_y;
	int	delta_x;

    (void)y;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	delta_x = x - center_x;
    data->player->rotation_angle += delta_x * data->player->rotation_speed;
    mlx_mouse_move(data->mlx->init, data->mlx->win, center_x, center_y);
	return (0);
}
