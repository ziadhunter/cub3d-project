/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:29:10 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/01 16:38:08 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_space_or_wall(char c)
{
	if (c == ' ' || c == '1' || c == '\0')
		return (1);
	return (0);
}

void	check_extension(char *file_name, char *ext, t_map *map_info,
		t_db_pointer *pointers)
{
	int	fn;
	int	ex;

	fn = ft_strlen(file_name);
	ex = ft_strlen(ext);
	if (fn <= ex || ft_strncmp(file_name + fn - ex, ext, ex) != 0)
	{
		if (ft_strncmp(ext, ".cub", ex) == 0)
			error_exit(NULL, NULL, NULL,
				"Error\nInvalid file extension: expected .cub\n");
		else
			error_exit(map_info, NULL, pointers,
				"Error\nInvalid file extension: expected .xpm\n");
	}
}

char	**get_lines_of_file(int fd)
{
	char	*line;
	char	*lines;
	char	**splited_lines;

	lines = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		lines = ft_strjoin(lines, line);
		line = get_next_line(fd);
	}
	splited_lines = ft_split(lines, '\n');
	free(lines);
	return (splited_lines);
}

int	ft_atoi_c(const char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] && (str[i] != '\n' || (str[i] == '\n' && i == 0)))
		return (-1);
	result *= sign;
	if (result > 255 || result < 0)
		return (-1);
	return (result);
}

int	is_map_element(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == 'D')
		return (1);
	return (0);
}
