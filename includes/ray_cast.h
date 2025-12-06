#ifndef RAY_CAST_H
#define RAY_CAST_H

#include <cub3d.h>

typedef struct s_facing_direction t_facing;
typedef struct s_ray t_ray;
typedef struct s_direction t_direction;

/*RAY-CASTING*/
void	facing_direction(double ray_angle, t_facing *dir);
int	wall(t_data *data, double x, double y);
void	insert_end_ray(t_ray *ray, t_direction *dir);
double	normalize_angle(double angle);
void	short_ray(t_data *data, t_ray *ray, t_direction *horizontal_inters,
		t_direction *vertical_inters);
void find_horizontal_intersiction(
	t_data *data, double ray_angle, t_facing facing, t_direction *horz_inter);
void find_vertical_intersiction(
	t_data *data, double ray_angle, t_facing facing, t_direction *vert_inter);
void	define_ray_position(t_data *data, double ray_angle, t_ray *ray);
void	creat_ray_casting(t_data *data);

#endif