/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouvement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:23:11 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/11 15:24:37 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		free_all_data_and_exit(data, "you exit the game!!\n");
	// else if (key == HOLD_GUN || key == HOLD_KNIFE)
	// 	switch_weapon(key, data);
	// else if (key == RELOAD)
	// 	reload_gun(key, data);
	else if (key == SPEED_DOWN || key == SPEED_UP || key == R_SPEED_DOWN || key == R_SPEED_UP || key == SHIFT_SPEED)
		speed_adjustment(key, data);
	else if (key == LEFT_BUTTON || key == RIGHT_BUTTON || key == DOWN_BUTTON || key == UP_BUTTON)
		mouvement_adjustment(key, data);
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		rotation_adjustment(key, data);
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

int	close_window(t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx->init);
	free_all_data_and_exit(data, "you exit the game!!\n");
	return (0);
}
