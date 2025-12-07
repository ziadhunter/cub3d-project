#ifndef RAY_CAST_H
#define RAY_CAST_H

#include <cub3d.h>

typedef struct s_facing_direction t_facing;
typedef struct s_ray t_ray;
typedef struct s_direction t_direction;

typedef struct s_ray_info
{
	double	x_step;
	double	y_step;
	double	x_intr;
	double	y_intr;
} t_ray_info;

/*RAY-CASTING*/
void	facing_direction(double ray_angle, t_ray *ray);
int	wall(t_data *data, double x, double y);
int is_door(t_data *data, double x, double y, double offset);
void	insert_end_ray(t_ray *ray, t_direction *dir, int intersection);
double	normalize_angle(double angle);
void	short_ray(t_data *data, t_ray *ray, t_direction *horizontal_inters,
		t_direction *vertical_inters);
void find_horizontal_intersiction(
	t_data *data, double ray_angle, t_ray *ray, t_direction *horz_inter);
void find_vertical_intersiction(
	t_data *data, double ray_angle, t_ray *ray, t_direction *vert_inter);
void	define_ray_position(t_data *data, double ray_angle, t_ray *ray);
void	creat_ray_casting(t_data *data);

#endif