/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knife_rendring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:34:12 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/10 18:46:16 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	render_knife_show(t_data *data)
{
	put_image_to_new_window(&data->new_image, &data->player->knife->knife_show,  data->player->knife->knif_s_i * WIN_WIDTH);
	data->player->knife->knif_s_i++;
	if (data->player->knife->knif_s_i == data->player->knife->knif_s_n)
	{
		data->player->knife->knif_s_i = 0;
		data->player->knife->knife_state = 'N';
	}
}

void	render_knife_hit(t_data *data)
{
	put_image_to_new_window(&data->new_image, &data->player->knife->knife_show,  data->player->knife->knif_h_i * WIN_WIDTH);
	data->player->knife->knif_h_i++;
	if (data->player->knife->knif_h_i == data->player->knife->knif_h_n)
	{
		data->player->knife->knif_h_i = 0;
		data->player->knife->knife_state = 'N';
	}
}

void	render_knife_move(t_data *data)
{
	put_image_to_new_window(&data->new_image, &data->player->knife->knife_show,  data->player->knife->knif_m_i * WIN_WIDTH);
	data->player->knife->knif_m_i++;
	if (data->player->knife->knif_m_i == data->player->knife->knif_m_n)
	{
		data->player->knife->knif_m_i = 0;
		data->player->knife->knife_state = 'N';
	}
}

void render_knife(t_data *data)
{
    if (data->player->knife->knife_state == 'S')
        render_knife_show(data);
    else if(data->player->knife->knife_state == 'H')
        render_knife_hit(data);
    else
        render_knife_move(data);
}