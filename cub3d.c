/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:41:23 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/13 21:20:17 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	int			i;
	t_data		*data;
	t_map_data	*map;

	i = 0;
	if (argc == 2)
	{
		data = parsing(argv[1]);
		map = data->map_info;
		start_the_game(data);
		free_data(data);
	}
	return (0);
}
