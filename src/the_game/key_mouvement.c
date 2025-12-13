/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouvement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:23:11 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/09 20:39:08 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

int	key_press(int key, t_data *data)
{
	char e[2][5] = {"hors", "vert"};
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
	else if (key == 'e')
		update_door_state(data);
	else if (key == 'p')
	{
		printf("Player position: x = %f, y = %f\n", data->player->x, data->player->y);
		printf("Player rotation angle: %f\n", data->player->rotation_angle);
		for (int i = 0; i < NUM_COLUMNS; i++)
		{
			printf("Ray: %s, %d: start_x = %d, start_y = %d, end_x = %d, end_y = %d, angle = %f\n",
				e[data->rays[i]->intersection - 1],
				i, data->rays[i]->start_x, data->rays[i]->start_y,
				data->rays[i]->end_x, data->rays[i]->end_y,
				data->rays[i]->ray_angle);
		}
	}
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
