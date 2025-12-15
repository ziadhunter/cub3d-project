/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_the_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:27:12 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/15 12:09:53 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	find_empty_line(t_map_data *map_info, char **lines, char *line, int fd)
{
	while (line)
	{
		if (line[0] == '\n')
		{
			while (line)
			{
				if (line[0] != '\n')
				{
					close(fd);
					free(line);
					error_exit(map_info, lines, NULL,
						"Error\nempty line inside map\n");
				}
				free(line);
				line = get_next_line(fd);
			}
			return ;
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	check_empty_line(t_map_data *map_info, char **lines, char *file_name)
{
	int		fd;
	char	*line;
	// int		i;

	// i = map_info->map_start;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (ft_strncmp(lines[0], line, ft_strlen(lines[0])) != 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	find_empty_line(map_info, lines, line, fd);
	close(fd);
}

char	**set_new_lines(int len, int characters, char **lines)
{
	char	**new_lines;
	int		i;

	i = 0;
	if (len <= 0)
	{
		free_double_pointer(lines);
		return (NULL);
	}
	new_lines = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		new_lines[i] = malloc(sizeof(char) * (characters + 1));
		ft_memset(new_lines[i], ' ', characters);
		new_lines[i][characters] = '\0';
		i++;
	}
	new_lines[i] = NULL;
	return (new_lines);
}

char	**rebuild_map_with_same_size(t_map_data *map, char **lines, int start)
{
	int		i;
	int		max_lenght;
	int		current_lenght;
	char	**new_lines;

	i = start;
	max_lenght = 0;
	while (lines[i])
	{
		current_lenght = ft_strlen(lines[i]);
		if (max_lenght < current_lenght)
			max_lenght = current_lenght;
		i++;
	}
	map->rows = i - start;
	map->columns = max_lenght;
	new_lines = set_new_lines(i - start, max_lenght, lines);
	if (!new_lines)
		return (NULL);
	i = -1;
	while (new_lines[++i])
		ft_strlcpy(new_lines[i], lines[start + i], max_lenght + 1);
	free_double_pointer(lines);
	return (new_lines);
}

t_data	*parsing_the_map(t_map_data *map_info, char **lines, char *file_name)
{
	t_player	*player;
	t_data		*data;

	lines = rebuild_map_with_same_size(map_info, lines, map_info->map_start);
	if (!lines)
		error_exit(map_info, NULL, NULL, "Error\nmap missing\n");
	check_empty_line(map_info, lines, file_name);
	player = valid_map(map_info, lines, 0, 0);
	if (!player)
		error_exit(map_info, lines, NULL, "Error\nmissing a player\n");
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
	{
		perror("ft_calloc");
		return (NULL);
	}
	data->map_info = map_info;
	data->player = player;
	data->hide_mousse = false;
	return (data);
}
