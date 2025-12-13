/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:13:01 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/09 04:44:19 by radouane         ###   ########.fr       */
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
	static unsigned int	l;
	// int					i;
	// int					j;

	l = 0;
	// i = 0;
	// j = 0;
	update_palyer_state(data, data->player);
	creat_ray_casting(data);
	projaction(data);
	render_mini_map(data);
	// BUG: the door is not detected when loking left or up
	door_check_using_rays(data);
	update_all_doors_state(data->doors_list);
	draw_cross_hair(data);
	// if (data->player->gun_or_knife == 1)
	// 	render_gun(data);
	// else
	// 	render_knife(data);
	mlx_put_image_to_window(data->mlx->init, data->mlx->win,
		data->new_image.img, 0, 0);
	l++;
	return (0);
}

void	start_the_game(t_data *data)
{
	initialization(data);
	load_game_data(data);
	data->map = create_map(data, data->map_info->map);
	//??chno kadir hadi akhay radouane?
	mlx_do_key_autorepeatoff(data->mlx->init);
	// mlx_hook(data->mlx->win, 4, 1L<<2, mouse_press, data);
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx->win, 17, 1L << 17, close_window, data);
	mlx_loop_hook(data->mlx->init, the_animation, data);
	mlx_loop(data->mlx->init);
	// mlx_do_key_autorepeaton(data->mlx->init);
}
