#include <cub3d.h>

void get_info_about_target_cell(t_data *data, t_ray *ray)
{
    t_door *door;

    if (data->map[(int)(ray->end_y / TILE_SIZE)][(int)(ray->end_x / TILE_SIZE)].cell_type == DOOR)
    {
        door = (t_door *)(data->map[(int)(ray->end_y / TILE_SIZE)][(int)(ray->end_x / TILE_SIZE)].options);
        if (door->is_valid)
        {
            ray->hit_cell = &data->textures.door;
            if (ray->intersection == HORIZONTAL)
                ray->x_offset = ray->end_x % TILE_SIZE + (TILE_SIZE - door->door_position);
            else if (ray->intersection == VERTICAL)
                ray->x_offset = ray->end_y % TILE_SIZE + (TILE_SIZE - door->door_position);
            return ;
        }
    }

    if (ray->intersection == HORIZONTAL)
    {
        ray->x_offset = ray->end_x % TILE_SIZE;
        if (ray->ray_direction.y < 0)
        {
            if (data->map[(int)((ray->end_y - 2) / TILE_SIZE)][(int)(ray->end_x / TILE_SIZE)].cell_type == DOOR)
                ray->hit_cell = &data->textures.door_inside;
            else
                ray->hit_cell = &data->textures.ea;
            ray->x_offset = (TILE_SIZE - ray->x_offset);
        }
        else
        {
            if (data->map[(int)((ray->end_y + 2) / TILE_SIZE)][(int)(ray->end_x / TILE_SIZE)].cell_type == DOOR)
                ray->hit_cell = &data->textures.door_inside;
            else
                ray->hit_cell = &data->textures.we;
        }
    }
    else
    {
        ray->x_offset = ray->end_y % TILE_SIZE;
        if (ray->ray_direction.x > 0)
        {
            if (data->map[(int)(ray->end_y / TILE_SIZE)][(int)((ray->end_x + 2) / TILE_SIZE)].cell_type == DOOR)
                ray->hit_cell = &data->textures.door_inside;
            else
                ray->hit_cell = &data->textures.no;
            ray->x_offset = (TILE_SIZE - ray->x_offset);
        }
        else
        {
            if (data->map[(int)(ray->end_y / TILE_SIZE)][(int)((ray->end_x - 2) / TILE_SIZE)].cell_type == DOOR)
                ray->hit_cell = &data->textures.door_inside;
            else
                ray->hit_cell = &data->textures.so;
        }
    }   

}