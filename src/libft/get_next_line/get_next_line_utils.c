/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:46:20 by rabounou          #+#    #+#             */
/*   Updated: 2025/03/23 06:09:36 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	appendto_buffer(char *tmp, t_buf *buffer, char **line)
{
	int	i;

	i = 0;
	while (tmp[i] && buffer->idx < 2047)
	{
		buffer->str[(buffer->idx)++] = tmp[i];
		if (tmp[i++] == '\n')
			break ;
	}
	(buffer->str)[buffer->idx] = '\0';
	if (tmp[i] && buffer->idx == 2047)
	{
		appendto_line(line, buffer->str);
		buffer->idx = 0;
		appendto_buffer(tmp + i, buffer, line);
	}
}

char	*last_clean(char *s, void (*f)(void *))
{
	int		i;
	int		j;
	char	*last;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0' || s[i + 1] == '\0')
		last = NULL;
	else
	{
		j = i + 1;
		last = ft_strdup(s + j);
	}
	if (f && s)
		f(s);
	return (last);
}

int	nl_found(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (s[i] == '\n');
}
