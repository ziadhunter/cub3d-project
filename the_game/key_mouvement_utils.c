/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouvement_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:15:59 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/02 18:03:33 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	speed_adjustment(int key, t_data *data)
{
	if (key == 49)
		if (data->player->walking_speed > MIN_WALK_SPEED)
			data->player->walking_speed -= 0.25;
	if (key == 50)
		if (data->player->walking_speed < MAX_WALK_SPEED)
			data->player->walking_speed += 0.25;
	if (key == 51)
		if (data->player->rotation_speed > MIN_ROTATION_SPEED)
			data->player->rotation_speed -= 0.0015;
	if (key == 52)
		if (data->player->rotation_speed < MAX_ROTATION_SPEED)
			data->player->rotation_speed += 0.0015;
}

void	mouvement_adjustment(int key, t_data *data)
{
	if (key == 'a')
	{
		data->player->old_move->left = 1;
		data->player->left_right = -1;
	}
	else if (key == 'd')
	{
		data->player->old_move->right = 1;
		data->player->left_right = 1;
	}
	else if (key == 's')
	{
		data->player->old_move->back = 1;
		data->player->back_forw = -1;
	}
	else if (key == 'w')
	{
		data->player->old_move->forw = 1;
		data->player->back_forw = 1;
	}
}

void	rotation_adjustment(int key, t_data *data)
{
	if (key == LEFT)
	{
		data->player->old_move->turn_left = 1;
		data->player->turn = -1;
	}
	else if (key == RIGHT)
	{
		data->player->old_move->turn_right = 1;
		data->player->turn = 1;
	}
}

void	rotation_release(int key, t_data *data)
{
	if (key == LEFT)
	{
		data->player->old_move->turn_left = 0;
		if (data->player->old_move->turn_right)
			data->player->turn = 1;
		else
			data->player->turn = 0;
	}
	else if (key == RIGHT)
	{
		data->player->old_move->turn_right = 0;
		if (data->player->old_move->turn_left)
			data->player->turn = -1;
		else
			data->player->turn = 0;
	}
}

void	mouvement_release(int key, t_data *data)
{
	if (key == 'a')
	{
		data->player->old_move->left = 0;
		if (data->player->old_move->right)
			data->player->left_right = 1;
		else
			data->player->left_right = 0;
	}
	else if (key == 'd')
	{
		data->player->old_move->right = 0;
		if (data->player->old_move->left)
			data->player->left_right = -1;
		else
			data->player->left_right = 0;
	}
	else if (key == 's')
	{
		data->player->old_move->back = 0;
		if (data->player->old_move->forw)
			data->player->back_forw = 1;
		else
			data->player->back_forw = 0;
	}
	else if (key == 'w')
	{
		data->player->old_move->forw = 0;
		if (data->player->old_move->forw)
			data->player->back_forw = 1;
		else
			data->player->back_forw = 0;
	}
}
