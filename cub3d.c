/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:41:23 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/07 22:39:38 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	// int		i;
	int		j;
	t_data	*data;
	t_map_data	*map;

	// i = 0;
	j = 0;
	if (argc == 2)
	{
		data = parsing(argv[1]);
		printf("all good\n");
		map = data->map_info;
		printf("floor :%d, %d, %d\n", map->f[0], map->f[1], map->f[2]);
		printf("ceiling :%d, %d, %d\n", map->c[0], map->c[1], map->c[2]);
		printf("north wall :%s\n", map->no);
		printf("south wall :%s\n", map->so);
		printf("east wall :%s\n", map->ea);
		printf("west wall :%s\n", map->we);
		printf("rows --> %d\n columns --> %d\n", map->rows, map->columns);
		while (map->map[j])
		{
			printf("%s\n", map->map[j]);
			j++;
		}
		start_the_game(data);
		free_data(data);
	}
}