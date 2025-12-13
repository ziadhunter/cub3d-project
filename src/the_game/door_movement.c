/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:11:36 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/13 22:19:05 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	update_door_state(t_data *data)
{
	t_door	*door;

	door = data->player->door;
	if (door == NULL)
		return ;
	if (door->door_state <= OPENED)
		door->door_state = CLOSING;
	else if (door->door_state >= CLOSED)
		door->door_state = OPENING;
}

void	update_all_doors_state(t_dlist *head)
{
	t_door	*door;

	while (head)
	{
		door = head->door;
		if (door->door_state == CLOSING)
		{
			if (door->door_position++ >= TILE_SIZE - 1)
				door->door_state = CLOSED;
		}
		else if (door->door_state == OPENING)
		{
			if (door->door_position-- <= 1)
				door->door_state = OPENED;
		}
		head = head->next;
	}
}
