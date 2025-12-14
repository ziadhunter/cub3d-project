/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:43:37 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/14 20:29:50 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_press(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 1)
		if (data->player->knife.knife_state == 'N')
			data->player->knife.knife_state = 'H';
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
	delta_x = (x - center_x) / 2;
	data->player->rotation_angle += delta_x * data->player->rotation_speed;
	mlx_mouse_move(data->mlx->init, data->mlx->win, center_x, center_y);
	return (0);
}
