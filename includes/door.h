/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:28:15 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/19 12:17:20 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include <cub3d.h>
# include <ray_cast.h>

typedef enum e_door_state
{
	OPENING,
	OPENED,
	CLOSED,
	CLOSING
}					t_door_state;

typedef struct s_door
{
	bool			is_valid;
	t_door_state	door_state;
	int				door_position;
}					t_door;

typedef struct s_dlist
{
	t_door			*door;
	struct s_dlist	*next;
}					t_dlist;

t_dlist				*new_dnode(t_door *door);
void				append_dnode(t_dlist **head, t_dlist *node);
void				append_door(t_dlist **head, t_door *door);
void				clear_dlist(t_dlist **head);

bool				is_dwall(t_data *data, t_ray_info ray_info,
						t_direction *intr, int intersection_type);

int					door_is_valid(t_data *data, char **map, int x, int y);
void				door_check_using_rays(t_data *data);
void				update_door_state(t_data *data);
void				update_all_doors_state(t_dlist *head);

#endif