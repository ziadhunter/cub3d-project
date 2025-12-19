/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:29:10 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/19 11:55:21 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_extension(char *file_name, char *ext, t_map_data *map_info,
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
	char	*tmp;
	char	**splited_lines;

	lines = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = lines;
		lines = ft_strjoin(lines, line);
		free(tmp);
		free(line);
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
		if (result_out_of_range(result * sign))
			return (-1);
		i++;
	}
	if (str[i] && (str[i] != '\n' || (str[i] == '\n' && i == 0)))
		return (-1);
	result *= sign;
	return (result);
}
