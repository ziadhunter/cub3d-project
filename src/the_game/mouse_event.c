/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:43:37 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/10 18:42:29 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int mouse_press(int key, int x, int y, t_data *data)
{
    if (key == 1)
    {
        if (data->player->gun_or_knife && data->player->gun->gun_state == 'N')
            if (data->player->gun->bullets_in_chamber > 0) 
                data->player->gun->gun_state = 'F';
        else if (!data->player->gun_or_knife && data->player->knife->knife_state == 'N')
            data->player->knife->knife_state = 'H';
    }
}
