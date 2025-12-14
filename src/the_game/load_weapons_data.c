/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapons_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:06:03 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/14 02:38:43 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	load_weapons(t_data *data)
{
	// load_xpm(data, "textures/knife_hit.xpm",
	// 	&(data->player->knife.knife_hit));
	// data->player->knife.knif_h_i = 0;
	// data->player->knife.knif_h_i = 20;
	load_xpm(data, "textures/knife_move.xpm",
		&(data->player->knife.knife_move));
	data->player->knife.knif_m_i = 0;
	data->player->knife.knif_m_n = 19;
}
