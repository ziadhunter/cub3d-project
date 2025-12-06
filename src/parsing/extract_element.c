/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:19:34 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/01 13:33:22 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	add_floor(t_map_data *map, char **str, char **lines, int i)
{
	char	**values;

	if (map->f)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nfloor element duplicated\n");
	values = ft_split(str[1], ',');
	if (!values)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nthere is no floor values\n");
	map->f = malloc(sizeof(int) * 3);
	while (++i < 3)
	{
		if (!values[i])
			error_exit(map, values, &(t_db_pointer){lines, str},
				"Error\nmissing floor values\n");
		map->f[i] = ft_atoi_c(values[i]);
		if (map->f[i] == -1)
			error_exit(map, values, &(t_db_pointer){lines, str},
				"Error\nwrong floor value\n");
	}
	if (str[2] || values[3])
		error_exit(map, values, &(t_db_pointer){lines, str},
			"Error\n extra floor argument\n");
	free_double_pointer(values);
}

void	which_element(char **line, int index, t_map_data *map, t_element element[6])
{
	char	**splited_line;
	int		i;

	i = 0;
	splited_line = ft_split(line[index], ' ');
	if (splited_line == NULL)
		return ;
	while (i < 6)
	{
		if (ft_strncmp(splited_line[0], element[i].type, element[i].length
				+ 1) == 0)
		{
			element[i].handle(map, splited_line, line, -1);
			free_double_pointer(splited_line);
			return ;
		}
		i++;
	}
	free_double_pointer(splited_line);
	free_double_pointer(line);
	error_exit(map, NULL, NULL, "Error\nwrong element\n");
}

int	all_element_found(t_map_data *map)
{
	if (map->c && map->f && map->no && map->so && map->ea && map->we)
		return (1);
	return (0);
}

int	quick_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_map_element(line[i]) || (line[i] == '\n' && i != 0))
		{
			i++;
			continue ;
		}
		return (0);
	}
	return (1);
}

t_map_data	*extract_element(char **lines)
{
	t_map_data		*map;
	int			i;
	t_element	elements[6];

	i = 0;
	initialize_element(&elements);
	map = initialize_map();
	while (lines[i])
	{
		if (quick_check(lines[i]))
			break ;
		which_element(lines, i, map, elements);
		i++;
	}
	if (!all_element_found(map))
	{
		free_double_pointer(lines);
		error_exit(map, NULL, NULL, "Error\nmissing some element(s)!!");
	}
	map->map_start = i;
	return (map);
}
