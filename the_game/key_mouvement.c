/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_mouvement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:23:11 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/01 18:17:40 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		free_all_data_and_exit(data, "you exit the game!!\n");
	if (key == 49 || key == 50 || key == 51 || key == 52)
	{
		speed_adjustment(key, data);
	}
	if (key == 'a' || key == 'd' || key == 's' || key == 'w')
	{
		mouvement_adjustment(key, data);
	}
	if (key == LEFT || key == RIGHT)
	{
		rotation_adjustment(key, data);
	}
	return (0);
}
int	key_release(int key, t_data *data)
{
	if (key == 'a' || key == 'd' || key == 's' || key == 'w')
	{
		mouvement_release(key, data);
	}
	if (key == LEFT || key == RIGHT)
	{
		rotation_release(key, data);
	}
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	old_x;
	static int	old_y;
	int			delta_x;
	int			delta_y;

	old_x = -1;
	old_y = -1;
	if (old_x == -1 && old_y == -1)
	{
		old_x = x;
		old_y = y;
		return (0);
	}
	delta_x = x - old_x;
	delta_y = y - old_y;
	if (delta_x != 0)
	{
		data->player->rotation_angle += delta_x * 0.002;
	}
	old_x = x;
	old_y = y;
	return (0);
}

int	close_window(t_data *data)
{
	free_all_data_and_exit(data, "you exit the game!!\n");
	return (0);
}