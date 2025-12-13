/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouvement_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:15:59 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/13 22:26:36 by rabounou         ###   ########.fr       */
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

void	mouvement_release(int keycode, t_data *data)
{
	if (keycode == UP_BUTTON && data->player->walk_direction.now == 1)
	{
		data->player->walk_direction.now = data->player->walk_direction.before;
		data->player->walk_direction.before = 0;
	}
	else if (keycode == DOWN_BUTTON && data->player->walk_direction.now == -1)
	{
		data->player->walk_direction.now = data->player->walk_direction.before;
		data->player->walk_direction.before = 0;
	}
	else if (keycode == RIGHT_BUTTON && data->player->side_direction.now == 1)
	{
		data->player->side_direction.now = data->player->side_direction.before;
		data->player->side_direction.before = 0;
	}
	else if (keycode == LEFT_BUTTON && data->player->side_direction.now == -1)
	{
		data->player->side_direction.now = data->player->side_direction.before;
		data->player->side_direction.before = 0;
	}
}

void	switch_weapon(int key, t_data *data)
{
	if (key == HOLD_GUN)
	{
		if (data->player->gun_or_knife)
			return ;
		else
		{
			data->player->gun.gun_state = 'S';
			data->player->gun_or_knife = 1;
		}
	}
	else
	{
		if (!data->player->gun_or_knife)
			return ;
		else
		{
			data->player->knife.knife_state = 'S';
			data->player->gun_or_knife = 0;
		}
	}
}
/*
void reload_gun(int key, t_data *data)
{
	if (data->player->gun_or_knife)
	{
		if (data->player->gun->gun_state == 'N')
		{
			data->player->gun->gun_state = 'R';
		}
	}
}*/