/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:20:34 by rabounou          #+#    #+#             */
/*   Updated: 2025/03/23 06:09:30 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	appendto_line(char **line, char *buffer)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = malloc((ft_strlen(*line) + ft_strlen(buffer) + 1)
			* sizeof(char));
	if (new_line == NULL)
	{
		free(*line);
		*line = NULL;
		return ;
	}
	i = 0;
	while (*line && (*line)[i])
	{
		new_line[i] = (*line)[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		new_line[i++] = buffer[j++];
	new_line[i] = '\0';
	free(*line);
	*line = new_line;
}

int	read_from_last(char **last, t_buf *buffer, char **line)
{
	if (nl_found(*last))
	{
		appendto_buffer(*last, buffer, line);
		appendto_line(line, buffer->str);
		if (*line == NULL)
		{
			free(*last);
			*last = NULL;
		}
		*last = last_clean(*last, free);
		return (0);
	}
	else
	{
		appendto_buffer(*last, buffer, line);
		free(*last);
		*last = NULL;
	}
	return (1);
}

int	read_from_file(char **last, t_buf *buffer, char **line, int fd)
{
	ssize_t	size;

	size = 1;
	while (size > 0)
	{
		size = read(fd, buffer->b_tmp, BUFFER_SIZE);
		buffer->b_tmp[size] = '\0';
		appendto_buffer(buffer->b_tmp, buffer, line);
		if (nl_found(buffer->b_tmp))
			break ;
	}
	if (size <= 0 && buffer->idx == 0)
		return (0);
	appendto_line(line, buffer->str);
	if (*line == NULL)
		return (0);
	*last = last_clean(buffer->b_tmp, NULL);
	return (1);
}

char	*cleanup(char **d1, char **d2, char **d3, char *return_value)
{
	if (d1 && *d1)
	{
		free(*d1);
		*d1 = NULL;
	}
	if (d2 && *d2)
	{
		free(*d2);
		*d2 = NULL;
	}
	if (d3 && *d3)
	{
		free(*d3);
		*d3 = NULL;
	}
	return (return_value);
}

char	*get_next_line(int fd)
{
	static char	*last;
	t_buf		buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	if (read(fd, 0, 0) == -1)
		return (cleanup(&last, NULL, NULL, NULL));
	buffer.b_tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer.b_tmp == NULL)
		return (cleanup(&(buffer.b_tmp), &last, NULL, NULL));
	buffer.idx = 0;
	buffer.b_tmp[0] = 0;
	line = NULL;
	if (last && read_from_last(&last, &buffer, &line) == 0)
		return (cleanup(&(buffer.b_tmp), NULL, NULL, line));
	if (last == NULL && read_from_file(&last, &buffer, &line, fd) == 0)
		return (cleanup(&(buffer.b_tmp), NULL, NULL, NULL));
	free(buffer.b_tmp);
	return (line);
}
