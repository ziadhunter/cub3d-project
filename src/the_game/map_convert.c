#include "cub3d.h"

int door_is_valid(t_data *data, char **map, int x, int y)
{
    int calc[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int type = 0;
    int i = 0;
    int targ_x, targ_y;

    while (i < 4)
    {
        targ_x = calc[i][0] + x;
        targ_y = calc[i][1] + y;
        if (targ_x > data->map_info->columns || targ_y > data->map_info->rows  || targ_x < 0 || targ_y < 0)
            return (0);
        type <<= 1;
        type |= map[targ_y][targ_x] == '1';
        i++;
    }
    // validate the door
    return (type == 3 || type == 12);
}

t_cell  **create_map(t_data *data, char **char_map)
{
    t_cell **map;
    int i, j;

    map = (t_cell **) malloc(data->map_info->rows * sizeof(t_cell *));
    
    i = 0;
    while (i < data->map_info->rows)
    {
        j = 0;
        map[i] = (t_cell *) malloc(data->map_info->columns * sizeof(t_cell));
        while (j < data->map_info->columns)
        {
            map[i][j].options = NULL;
            if (char_map[i][j] == 'D')
            {
                map[i][j].cell_type = DOOR;
                map[i][j].options = (t_door *) malloc (sizeof(t_door));
                ((t_door *)(map[i][j].options))->is_valid = door_is_valid(data, char_map, j, i);
                ((t_door *)(map[i][j].options))->door_state = CLOSED;
                ((t_door *)(map[i][j].options))->door_position = TILE_SIZE;
                append_door(&(data->doors_list), map[i][j].options);
            }
            else if (char_map[i][j] == '1')
                map[i][j].cell_type = WALL;
            else if (char_map[i][j] == ' ')
                map[i][j].cell_type = SPACE;
            j++;
        }
        i++;
    }
    return (map);
}
