/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouvement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:23:11 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/17 15:59:12 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		free_all_data_and_exit(data, "you exit the game!!\n", EXIT_SUCCESS);
	else if (key == SPEED_DOWN || key == SPEED_UP || key == R_SPEED_DOWN
		|| key == R_SPEED_UP || key == SHIFT_SPEED)
		speed_adjustment(key, data);
	else if (key == LEFT_BUTTON || key == RIGHT_BUTTON || key == DOWN_BUTTON
		|| key == UP_BUTTON)
		mouvement_adjustment(key, data);
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		rotation_adjustment(key, data);
	else if (key == 'e')
		update_door_state(data);
	else if (key == MOUSSE_HIDE)
		data->hide_mousse = !data->hide_mousse;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == LEFT_BUTTON || key == RIGHT_BUTTON || key == DOWN_BUTTON
		|| key == UP_BUTTON)
	{
		mouvement_release(key, data->player);
	}
	if (key == LEFT_ARROW || key == RIGHT_ARROW)
	{
		rotation_release(key, data);
	}
	if (key == SHIFT_SPEED)
		data->player->walking_speed -= 3;
	return (0);
}

int	close_window(t_data *data)
{
	free_all_data_and_exit(data, "you exit the game!!\n", EXIT_SUCCESS);
	return (0);
}
