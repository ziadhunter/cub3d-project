/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:23:11 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/01 13:33:16 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	add_ceiling(t_map_data *map, char **str, char **lines, int i)
{
	char	**values;

	if (map->c)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nceiling element duplicated\n");
	values = ft_split(str[1], ',');
	if (!values)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nthere is no ceiling value\n");
	map->c = malloc(sizeof(int) * 3);
	while (++i < 3)
	{
		if (!values[i])
			error_exit(map, values, &(t_db_pointer){lines, str},
				"Error\nmissing ceiling value\n");
		map->c[i] = ft_atoi_c(values[i]);
		if (map->c[i] == -1)
			error_exit(map, values, &(t_db_pointer){lines, str},
				"Error\nwrong ceiling value\n");
	}
	if (str[2] || values[3])
		error_exit(map, values, &(t_db_pointer){lines, str},
			"Error\n extra ceiling argument\n");
	free_double_pointer(values);
}

void	add_we(t_map_data *map, char **str, char **lines, int i)
{
	int	fdd;

	(void) i;
	if (map->we)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nWE element duplicated\n");
	if (str[1])
	{
		check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
		fdd = open(str[1], O_RDONLY);
		if (fdd < 0)
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nWE texture file doesn't exist\n");
		close(fdd);
		if (str[2])
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nextra argument of WE\n");
		map->we = ft_strdup(str[1]);
	}
	else
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nmissing WE file texture\n");
}

void	add_ea(t_map_data *map, char **str, char **lines, int i)
{
	int	fdd;

	(void) i;
	if (map->ea)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nEA element duplicated\n");
	if (str[1])
	{
		check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
		fdd = open(str[1], O_RDONLY);
		if (fdd < 0)
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nEA texture file doesn't exist\n");
		close(fdd);
		if (str[2])
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nextra argument of EA\n");
		map->ea = ft_strdup(str[1]);
	}
	else
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nmissing EA file texture\n");
}

void	add_so(t_map_data *map, char **str, char **lines, int i)
{
	int	fdd;

	(void) i;
	if (map->so)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nSO element duplicated\n");
	if (str[1])
	{
		check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
		fdd = open(str[1], O_RDONLY);
		if (fdd < 0)
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nSO texture file doesn't exist\n");
		close(fdd);
		if (str[2])
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nextra argument of SO\n");
		map->so = ft_strdup(str[1]);
	}
	else
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nmissing SO file texture\n");
}

void	add_no(t_map_data *map, char **str, char **lines, int i)
{
	int	fdd;

	(void) i;
	if (map->no)
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nNO element duplicated\n");
	if (str[1])
	{
		check_extension(str[1], ".xpm", map, &(t_db_pointer){str, lines});
		fdd = open(str[1], O_RDONLY);
		if (fdd < 0)
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nNO texture file doesn't exist\n");
		close(fdd);
		if (str[2])
			error_exit(map, lines, &(t_db_pointer){str, NULL},
				"Error\nextra argument of NO\n");
		map->no = ft_strdup(str[1]);
	}
	else
		error_exit(map, lines, &(t_db_pointer){str, NULL},
			"Error\nmissing NO file texture\n");
}
