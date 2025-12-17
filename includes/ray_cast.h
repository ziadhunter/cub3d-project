/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:28:31 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/17 16:46:24 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H

# include <cub3d.h>

typedef struct s_facing_direction	t_facing;
typedef struct s_ray				t_ray;
typedef struct s_data				t_data;
typedef struct s_player				t_player;
typedef struct s_img				t_img;

typedef struct s_direction
{
	double							x;
	double							y;
}									t_direction;

typedef struct s_ray_info
{
	double							x_step;
	double							y_step;
	double							x_intr;
	double							y_intr;
	t_direction						ray_direction;
}									t_ray_info;

/*RAY-CASTING*/
void	facing_direction(double ray_angle,
			t_ray *ray);
int		wall(t_data *data, double x, double y);
int		is_door(t_data *data, double x, double y,
			double offset);
void	insert_end_ray(t_ray *ray, t_direction *dir,
			int intersection);
double	normalize_angle(double angle);
void	short_ray(t_data *data, t_ray *ray,
			t_direction *horizontal_inters, t_direction *vertical_inters);
void	find_horizontal_intersiction(t_data *data, double ray_angle,
			t_ray *ray, t_direction *horz_inter);
void	find_vertical_intersiction(t_data *data, double ray_angle,
			t_ray *ray, t_direction *vert_inter);
void	define_ray_position(t_data *data,
			double ray_angle, t_ray *ray);
void	creat_ray_casting(t_data *data);
void	get_info_about_target_cell(t_data *data,
			t_ray *ray);
bool	targeted_cell_not_empty(t_data *data,
			t_ray_info ray_info, t_direction *inter, int intersection_type);

bool	ray_facing_up(t_direction dir);
bool	ray_facing_down(t_direction dir);
bool	ray_facing_left(t_direction dir);
bool	ray_facing_right(t_direction dir);

#endif