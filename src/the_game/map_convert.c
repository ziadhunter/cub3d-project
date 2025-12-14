/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:48:50 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/14 18:11:50 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	door_is_valid(t_data *data, char **map, int x, int y)
{
	static int	calc[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int			targ_x;
	int			targ_y;
	int			type;
	int			i;

	type = 0;
	i = 0;
	while (i < 4)
	{
		targ_x = calc[i][0] + x;
		targ_y = calc[i][1] + y;
		if (targ_x > data->map_info->columns || targ_y > data->map_info->rows
			|| targ_x < 0 || targ_y < 0)
			return (0);
		type <<= 1;
		type |= map[targ_y][targ_x] == '1';
		i++;
	}
	return (type == 3 || type == 12);
}

void	create_new_door(t_data *data, char **char_map, t_cell **map,
	t_icord idx)
{
	map[idx.y][idx.x].cell_type = DOOR;
	map[idx.y][idx.x].options = (t_door *)malloc(sizeof(t_door));
	((t_door *)(map[idx.y][idx.x].options))->is_valid = door_is_valid(data,
			char_map, idx.x, idx.y);
	((t_door *)(map[idx.y][idx.x].options))->door_state = CLOSED;
	((t_door *)(map[idx.y][idx.x].options))->door_position = TILE_SIZE;
	append_door(&(data->doors_list), map[idx.y][idx.x].options);
}

t_cell	**create_map(t_data *data, char **char_map)
{
	t_cell	**map;
	t_icord	idx;

	map = (t_cell **)malloc(data->map_info->rows * sizeof(t_cell *));
	data->doors_list = NULL;
	idx.y = 0;
	while (idx.y < data->map_info->rows)
	{
		idx.x = 0;
		map[idx.y] = (t_cell *)malloc(data->map_info->columns * sizeof(t_cell));
		while (idx.x < data->map_info->columns)
		{
			map[idx.y][idx.x].options = NULL;
			if (char_map[idx.y][idx.x] == 'D')
				create_new_door(data, char_map, map, idx);
			else if (char_map[idx.y][idx.x] == '1')
				map[idx.y][idx.x].cell_type = WALL;
			else
				map[idx.y][idx.x].cell_type = NONE;
			idx.x++;
		}
		idx.y++;
	}
	return (map);
}
