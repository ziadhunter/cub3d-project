#include "cub.h"

void *load_xpm(t_data *data, char *path, t_img *img)
{
	int width;
	int height;
	void *xpm;

	if (path == NULL)
		return (NULL);

	xpm = mlx_xpm_file_to_image(data->mlx->init, path, &(img->width), &(img->height));
	// if (width != 64 || height != 64)
	// {
	// 	printf("wrong xpm size: w: %d, h: %d\n", width, height);
	// 	mlx_destroy_image(data->mlx->init, xpm);
	// 	return (NULL);
	// }
	return (xpm);
}