#include <cub3d.h>

void load_xpm(t_data *data, char *path, t_img *img)
{

	if (path == NULL)
		return ;
	img->img = mlx_xpm_file_to_image(data->mlx->init, path, &(img->width), &(img->height));
    if (img->img == NULL)
    {
        perror("mlx_xpm_file_to_image: ");
        return ;
    }
    img->addr = mlx_get_data_addr(img->img, &img->bpp,
            &img->line_length, &img->endian);
}

void load_textures(t_data *data)
{
    // TODO: check if file exist first
    load_xpm(data, data->map_info->no, &(data->textures.no));
    load_xpm(data, data->map_info->so, &(data->textures.so));
    load_xpm(data, data->map_info->we, &(data->textures.we));
    load_xpm(data, data->map_info->ea, &(data->textures.ea));
    load_xpm(data, "textures/door.xpm", &(data->textures.door));
    load_xpm(data, "textures/door_in.xpm", &(data->textures.door_inside));
    load_xpm(data, "textures/close_door_btn.xpm", &(data->textures.close_door_btn));
    load_xpm(data, "textures/open_door_btn.xpm", &(data->textures.open_door_btn));
}

void load_game_data(t_data *data)
{
    load_textures(data);
}