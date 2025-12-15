/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapons_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:06:03 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/15 17:30:31 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	load_weapons(t_data *data)
{
	load_xpm(data, "textures/knife_attack.xpm",
		&(data->player->knife.knife_attack));
	data->player->knife.knif_a_i = 0;
	data->player->knife.knif_a_n = 20;
	load_xpm(data, "textures/knife_move.xpm",
		&(data->player->knife.knife_move));
	data->player->knife.knif_m_i = 0;
	data->player->knife.knif_m_n = 19;
}
