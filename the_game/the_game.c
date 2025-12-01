/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:13:01 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/01 17:46:43 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_wall(t_data *data, double *x, double *y)
{
	double	px;
	double	py;
	double	rx;
	double	ry;

	px = data->player->x / TILE_SIZE;
	py = data->player->y / TILE_SIZE;
	rx = *x / TILE_SIZE;
	ry = *y / TILE_SIZE;
	if (data->map_info->map[(int)ry][(int)rx] != '1')
		return (1);
	else if (data->map_info->map[(int)ry][(int)px] != '1')
	{
		*x = data->player->x;
		return (1);
	}
	else if (data->map_info->map[(int)py][(int)rx] != '1')
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

void	update_palyer_state(t_data *data, t_player *player)
{
	double	x;
	double	y;

	x = player->x;
	y = player->y;
	//update the x and y position of the player
	//ma39altch 3la hadchi tat3awed tfahmo!!!!!!!!!!!!!
	x += ((cos(player->rotation_angle) * player->walking_speed / 3)
			* player->back_forw);
	y += ((sin(player->rotation_angle) * player->walking_speed / 3)
			* player->back_forw);
	x += ((cos(player->rotation_angle + PI / 2) * player->walking_speed / 3)
			* player->left_right);
	y += ((sin(player->rotation_angle + PI / 2) * player->walking_speed / 3)
			* player->left_right);
	//check if the new position isn't a wall
	if (is_wall(data, &x, &y))
	{
		player->x = x;
		player->y = y;
	}
	//update the direction of the player
	data->player->rotation_angle += (data->player->rotation_speed
			* data->player->turn);
}

int	the_animation(t_data *data)
{
	static unsigned int	l;
	int					i;
	int					j;

	l = 0;
	i = 0;
	j = 0;
	update_palyer_state(data, data->player);
	creat_ray_casting(data);
	projaction(data);
	render_mini_map(data);
	mlx_put_image_to_window(data->mlx->init, data->mlx->win,
			data->new_image.img, 0, 0);
	l++;
	return (0);
}

void	start_the_game(t_data *data)
{
	initialization(data);
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx->win, 17, 1L << 17, close_window, data);
	mlx_loop_hook(data->mlx->init, the_animation, data);
	mlx_loop(data->mlx->init);
}