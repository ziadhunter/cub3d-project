/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouvement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:23:11 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/10 18:11:51 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		free_all_data_and_exit(data, "you exit the game!!\n");
	else if (key == HOLD_GUN || key == HOLD_KNIFE)
		switch_weapon(key, data);
	else if (key == RELOAD)
		reload_gun(key, data);
	else if (key == SPEED_DOWN || key == SPEED_UP || key == R_SPEED_DOWN || key == R_SPEED_UP)
		speed_adjustment(key, data);
	else if (key == LEFT_BUTTON || key == RIGHT_BUTTON || key == DOWN_BUTTON || key == UP_BUTTON)
		mouvement_adjustment(key, data);
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		rotation_adjustment(key, data);
	else if (key == RELOAD)
		reload_gun();
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == LEFT_BUTTON || key == RIGHT_BUTTON || key == DOWN_BUTTON || key == UP_BUTTON)
	{
		mouvement_release(key, data);
	}
	if (key == LEFT_ARROW || key == RIGHT_ARROW)
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
	// int			delta_y;

	old_x = -1;
	old_y = -1;
	if (old_x == -1 && old_y == -1)
	{
		old_x = x;
		old_y = y;
		return (0);
	}
	delta_x = x - old_x;
	// delta_y = y - old_y;
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
	mlx_do_key_autorepeaton(data->mlx->init);
	free_all_data_and_exit(data, "you exit the game!!\n");
	return (0);
}
