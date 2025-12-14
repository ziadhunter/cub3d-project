/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:24:31 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/14 16:54:44 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_space_or_nl(char c)
{
	if (c == ' ' || c == '\0')
		return (1);
	return (0);
}

t_map_data	*initialize_map(void)
{
	t_map_data	*map;

	map = malloc(sizeof(t_map_data));
	map->c = NULL;
	map->f = NULL;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->map = NULL;
	map->rows = 0;
	map->columns = 0;
	return (map);
}

// t_oldmove	*initialize_old_move(void)
// {
// 	t_oldmove	*old;

// 	old = malloc(sizeof(t_oldmove));
// 	old->back = 0;
// 	old->forw = 0;
// 	old->left = 0;
// 	old->right = 0;
// 	old->turn_left = 0;
// 	old->turn_right = 0;
// 	return (old);
// }


void initialize_knife(t_player *player)
{
	t_knife *knife;
	
	knife = &player->knife;
	knife->knife_state = 'N';
}

t_player	*initialize_player(char c, int x, int y)
{
	t_player	*player;
	// t_oldmove	*old;

	// old = initialize_old_move();
	player = malloc(sizeof(t_player));
	// player->old_move = old;
	player->x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	player->y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	player->radius = 9;
	// player->back_forw = 0;
	// player->left_right = 0;
	player->rotation_angle = 0;
	if (c == 'S')
		player->rotation_angle = PI / 2;
	if (c == 'N')
		player->rotation_angle = 3 * (PI / 2);
	if (c == 'W')
		player->rotation_angle = PI;
	player->walking_speed = 5;
	player->rotation_speed = (PI / 180);
	player->walk_direction.now = 0;
	player->walk_direction.before = 0;
	player->side_direction.now = 0;
	player->side_direction.before = 0;
	player->rotation_direction.now = 0;
	player->rotation_direction.before = 0;
	initialize_knife(player);
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
