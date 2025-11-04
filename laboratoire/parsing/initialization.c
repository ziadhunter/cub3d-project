/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:24:31 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/04 10:24:28 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_space_or_wall(char c)
{
	if (c == ' ' || c == '1' || c == '\0')
		return (1);
	return (0);
}

int	is_space_or_nl(char c)
{
	if (c == ' ' || c == '\0')
		return (1);
	return (0);
}

t_map	*initialize_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->c = NULL;
	map->f = NULL;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->map = NULL;
	map->map_height = 0;
	map->map_length = 0;
	return (map);
}

t_player	*initializechar c, t_player *player, t_oldmove *old)
{
	old = malloc(sizeof(t_oldmove));
	old->back = 0;
	old->forw = 0;
	old->left = 0;
	old->right = 0;
	old->turn_left = 0;
	old->turn_right = 0;
	player = malloc(sizeof(t_player));
	player->old_move = old;
	player->x = 7 * 64;
	player->y = 5 * 64;
	player->radius = 9;
	player->back_forw = 0;
	player->left_right = 0;
	player->rotation_angle = 0;
	if (c == 'S')
		player->rotation_angle = PI / 2;
	if (c == 'N')
		player->rotation_angle = 3 * (PI / 2);
	if (c == 'W')
		player->rotation_angle = PI;
	player->walking_speed = 2;
	player->rotation_speed = (PI / 180) / 2;
	return (player);
}

void	initialize_element(t_element (*element)[6])
{
	(*element)[0].type = "F";
	(*element)[0].length = 1;
	(*element)[0].handle = add_floor;
	(*element)[1].type = "C";
	(*element)[1].length = 1;
	(*element)[1].handle = add_ceiling;
	(*element)[2].type = "NO";
	(*element)[2].length = 2;
	(*element)[2].handle = add_no;
	(*element)[3].type = "SO";
	(*element)[3].length = 2;
	(*element)[3].handle = add_so;
	(*element)[4].type = "EA";
	(*element)[4].length = 2;
	(*element)[4].handle = add_ea;
	(*element)[5].type = "WE";
	(*element)[5].length = 2;
	(*element)[5].handle = add_we;
}
