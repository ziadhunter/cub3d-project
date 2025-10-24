#include "cub.h"

void *load_xpm(t_data *data, char *path)
{
	int width;
	int height;
	void *xpm;

	if (path == NULL)
		return (NULL);

	xpm = mlx_xpm_file_to_image(data->mlx->init, path, &width, &height);
	if (width != 64 || height != 64)
	{
		printf("wrong xpm size: w: %d, h: %d\n", width, height);
		mlx_destroy_image(data->mlx->init, xpm);
		return (NULL);
	}
	return (xpm);
}