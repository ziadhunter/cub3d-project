#include <cub3d.h>
#include <fcntl.h>
#include <sys/stat.h>

bool    file_exists(const char *path)
{
	if (path == NULL)
		return (false);
	if (access(path, F_OK) == 0)
		return (true);
	perror(path);
	return (false);
}

bool    file_readable(const char *path)
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
	struct stat sb;

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
