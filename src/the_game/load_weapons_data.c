/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapons_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:06:03 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/13 22:06:04 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	load_gun(t_data *data)
{
	load_xpm(data, "textures/wp/gun_reload.xpm",
		&(data->player->gun.gun_reload));
	data->player->gun.gr_i = 0;
	data->player->gun.gr_n = 21;
}

void	load_weapons(t_data *data)
{
	load_gun(data);
}
