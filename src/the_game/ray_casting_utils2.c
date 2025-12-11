#include <cub3d.h>


bool ray_facing_up(t_ray *ray)
{
    return (ray->ray_direction.y > 0);
}

bool ray_facing_down(t_ray *ray)
{
    return (ray->ray_direction.y < 0);
}

bool ray_facing_left(t_ray *ray)
{
    return (ray->ray_direction.x < 0);
}

bool ray_facing_right(t_ray *ray)
{
    return (ray->ray_direction.x > 0);
}
