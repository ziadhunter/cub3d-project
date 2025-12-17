/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:13:01 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/17 17:06:37 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <rendring.h>

int	is_wall(t_data *data, double *x, double *y)
{
	int	px;
	int	py;
	int	rx;
	int	ry;

	px = (int)(data->player->x / TILE_SIZE);
	py = (int)(data->player->y / TILE_SIZE);
	rx = (int)(*x / TILE_SIZE);
	ry = (int)(*y / TILE_SIZE);
	if (data->map[ry][rx].cell_type != WALL)
		return (1);
	else if (data->map[ry][px].cell_type != WALL)
	{
		*x = data->player->x;
		return (1);
	}
	else if (data->map[py][rx].cell_type != WALL)
	{
		*y = data->player->y;
		return (1);
	}
	return (0);
}

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	the_animation(t_data *data)
{
	update_palyer_state(data, data->player);
	creat_ray_casting(data);
	projaction(data);
	door_check_using_rays(data);
	update_all_doors_state(data->doors_list);
	render_knife(data);
	render_mini_map(data);
	mlx_put_image_to_window(data->mlx->init, data->mlx->win,
		data->new_image.img, 0, 0);
	return (0);
}

void	start_the_game(t_data *data)
{
	printf("max_rotation_speed = %f\n", data->player->rotation_speed);
	initialization(data);
	load_game_data(data);
	data->map = create_map(data, data->map_info->map);
	mlx_hook(data->mlx->win, 4, 1L << 2, mouse_press, data);
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx->win, 17, 1L << 17, close_window, data);
	mlx_loop_hook(data->mlx->init, the_animation, data);
	mlx_loop(data->mlx->init);
}
