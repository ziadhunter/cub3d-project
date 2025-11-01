/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:16:39 by zfarouk           #+#    #+#             */
/*   Updated: 2025/11/01 13:33:27 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_double_pointer(char **value)
{
	int	i;

	i = 0;
	if (value)
	{
		while (value[i])
		{
			free(value[i]);
			i++;
		}
		free(value);
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		if (map->c)
			free(map->c);
		if (map->f)
			free(map->f);
		if (map->ea)
			free(map->ea);
		if (map->no)
			free(map->no);
		if (map->so)
			free(map->so);
		if (map->we)
			free(map->we);
		if (map->map)
			free_double_pointer(map->map);
		free(map);
	}
}

void	free_data(t_data *data)
{
	free_map(data->map_info);
	free(data->player->old_move);
	free(data->player);
	free(data);
}

void	error_exit(t_map *map, char **value, t_db_pointer *double_pointers,
		char *str)
{
	printf("%s", str);
	if (value)
		free_double_pointer(value);
	if (double_pointers)
	{
		if (double_pointers->ptr)
			free_double_pointer(double_pointers->ptr);
		if (double_pointers->ptrr)
			free_double_pointer(double_pointers->ptrr);
	}
	free_map(map);
	exit(1);
}
