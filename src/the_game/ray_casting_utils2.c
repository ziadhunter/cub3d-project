#include <cub3d.h>


bool ray_facing_up(t_direction dir)
{
    return (dir.y > 0);
}

bool ray_facing_down(t_direction dir)
{
    return (dir.y < 0);
}

bool ray_facing_left(t_direction dir)
{
    return (dir.x < 0);
}

bool ray_facing_right(t_direction dir)
{
    return (dir.x > 0);
}
