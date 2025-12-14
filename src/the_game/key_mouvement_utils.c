/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouvement_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:15:59 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/14 02:20:17 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	mouvement_adjustment(int keycode, t_data *data)
{
	if (keycode == UP_BUTTON)
	{
		data->player->walk_direction.before = data->player->walk_direction.now;
		data->player->walk_direction.now = 1;
	}
	else if (keycode == DOWN_BUTTON)
	{
		data->player->walk_direction.before = data->player->walk_direction.now;
		data->player->walk_direction.now = -1;
	}
	else if (keycode == RIGHT_BUTTON)
	{
		data->player->side_direction.before = data->player->side_direction.now;
		data->player->side_direction.now = 1;
	}
	else if (keycode == LEFT_BUTTON)
	{
		data->player->side_direction.before = data->player->side_direction.now;
		data->player->side_direction.now = -1;
	}
}

void	rotation_adjustment(int keycode, t_data *data)
{
	if (keycode == RIGHT_ARROW)
	{
		data->player->rotation_direction.before
			= data->player->rotation_direction.before;
		data->player->rotation_direction.now = 1;
	}
	else if (keycode == LEFT_ARROW)
	{
		data->player->rotation_direction.before
			= data->player->rotation_direction.before;
		data->player->rotation_direction.now = -1;
	}
}

void	rotation_release(int keycode, t_data *data)
{
	if (keycode == RIGHT_ARROW)
	{
		if (data->player->rotation_direction.now == 1)
			data->player->rotation_direction.now
				= data->player->rotation_direction.before;
		data->player->rotation_direction.before = 0;
	}
	else if (keycode == LEFT_ARROW)
	{
		if (data->player->rotation_direction.now == -1)
			data->player->rotation_direction.now
				= data->player->rotation_direction.before;
		data->player->rotation_direction.before = 0;
	}
}

void	mouvement_release(int keycode, t_player *player)
{
	if (keycode == UP_BUTTON)
	{
		if (player->walk_direction.now == 1)
			player->walk_direction.now = player->walk_direction.before;
		player->walk_direction.before = 0;
	}
	else if (keycode == DOWN_BUTTON)
	{
		if (player->walk_direction.now == -1)
			player->walk_direction.now = player->walk_direction.before;
		player->walk_direction.before = 0;
	}
	else if (keycode == RIGHT_BUTTON)
	{
		if (player->side_direction.now == 1)
			player->side_direction.now = player->side_direction.before;
		player->side_direction.before = 0;
	}
	else if (keycode == LEFT_BUTTON)
	{
		if (player->side_direction.now == -1)
			player->side_direction.now = player->side_direction.before;
		player->side_direction.before = 0;
	}
}
