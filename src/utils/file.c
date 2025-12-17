/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:23:27 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/17 16:39:15 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <fcntl.h>
#include <sys/stat.h>

void	pput_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

bool	file_exists(const char *path)
{
	if (path == NULL)
		return (false);
	if (access(path, F_OK) == 0)
		return (true);
	perror(path);
	return (false);
}

bool	file_readable(const char *path)
{
	if (path == NULL)
		return (false);
	if (access(path, R_OK) == 0)
		return (true);
	perror(path);
	return (false);
}

bool	file_is_not_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return (false);
		}
		return (true);
	}
	perror("lstat");
	return (false);
}

bool	file_isvalid(char *path)
{
	return (file_exists(path) && file_readable(path) && file_is_not_dir(path));
}
