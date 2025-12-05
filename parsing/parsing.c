/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:51:17 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/04 11:23:38 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	invalid_position(t_map *map_info, t_player *player, char **lines,
		t_cord cor)
{
	int	i;
	int	j;

	i = cor.x;
	j = cor.y;
	if (i <= 0 || j <= 0 || i + 1 >= map_info->columns || j
		+ 1 >= map_info->rows)
	{
		if (player)
		{
			free(player->old_move);
			free(player);
		}
		error_exit(map_info, lines, NULL, "Error\ninvalid map (edge open)1\n");
	}
	if (is_space_or_nl(lines[j][i - 1]) || is_space_or_nl(lines[j - 1][i])
		|| is_space_or_nl(lines[j + 1][i]) || is_space_or_nl(lines[j][i + 1]))
	{
		if (player)
		{
			free(player->old_move);
			free(player);
		}
		error_exit(map_info, lines, NULL, "Error\ninvalid map (edge open)\n");
	}
}

void	check_element_position(t_map *map_info, t_player **player, char **lines,
		t_cord cor)
{
	int	i;
	int	j;

	i = cor.x;
	j = cor.y;
	invalid_position(map_info, *player, lines, cor);
	if (lines[j][i] == 'N' || lines[j][i] == 'S' || lines[j][i] == 'W'
		|| lines[j][i] == 'E')
	{
		lines[j][i] = '0';
		if (!(*player))
			*player = initialize_player(lines[j][i], i, j);
		else
		{
			free((*player)->old_move);
			free(*player);
			error_exit(map_info, lines, NULL,
				"Error\ninvalid map(two or more players)");
		}
	}
}

void	check_space_position(t_map *map_info, t_player *player, char **lines,
		t_cord cor)
{
	int	i;
	int	j;

	i = cor.x;
	j = cor.y;
	if (i <= 0 || j <= 0 || i >= map_info->columns || j
		+ 1 >= map_info->rows)
		return ;
	if (!is_space_or_wall(lines[j + 1][i]) ||
		!is_space_or_wall(lines[j - 1][i]) ||
		!is_space_or_wall(lines[j][i + 1]) ||
		!is_space_or_wall(lines[j][i - 1]))
	{
		if (player != NULL)
		{
			free(player->old_move);
			free(player);
		}
		error_exit(map_info, lines, NULL, "Error\ninvalid map");
	}
}

t_player	*valid_map(t_map *map_info, char **map, int i, int j)
{
	t_player	*player;

	player = NULL;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0' || map[j][i] == 'N' ||
				map[j][i] == 'S' || map[j][i] == 'E' || map[j][i] == 'W')
				check_element_position(map_info, &player, map, (t_cord){i, j});
			if (map[j][i] == ' ')
				check_space_position(map_info, player, map, (t_cord){i, j});
			i++;
		}
		j++;
	}
	map_info->map = map;
	return (player);
}

t_data	*parsing(char *file_name)
{
	int		fd;
	t_map	*map_info;
	t_data	*data;
	char	**lines;

	check_extension(file_name, ".cub", NULL, NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit(NULL, NULL, NULL, "Error\ncould not find the file\n");
	lines = get_lines_of_file(fd);
	close(fd);
	map_info = extract_element(lines);
	data = parsing_the_map(map_info, lines, file_name);
	return (data);
}
