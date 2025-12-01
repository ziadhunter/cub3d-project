/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_mouvement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:23:11 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/30 19:23:07 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void free_rays(t_ray **rays)
{
    int i;
    i = 0;
    while (i < NUM_COLUMNS)
        free(rays[i++]);
    free(rays);
}

void free_all_data_and_exit(t_data *data, char *str)
{
    mlx_destroy_image(data->mlx->init, data->new_image.img);
    free(data->mlx);
    free(data->player->old_move);
    free(data->player);
    free_rays(data->rays);
    free_map(data->map_info);
    free(data);
    printf("%s", str);
    exit(0);
}

void speed_adjustement(int key, t_data *data)
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

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		free_all_data_and_exit(data, "you exit the game!!\n");

    if (key == 49 || key == 50 || key == 51 || key == 52)
    {
        speed_adjustement(key, data);
    }
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
	return (0);
}

int	key_release(int key, t_data *data)
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
	return (0);
}


int mouse_mouve()

int close_window(t_data *data)
{
    free_all_data_and_exit(data, "you exit the game!!\n");
    return (0);
}