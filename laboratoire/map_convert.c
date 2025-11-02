#include "cub.h"

int get_map_height(char **map)
{
    int i;

    if (map == NULL)
        return (0);
    i = 0;
    while (map[i])
        i++;
    return (i);
}

int get_map_width(char **map)
{
    int i;

    i = 0;
    if (map == NULL || map[i] == NULL)
        return (0);
    while (map[0][i])
        i++;
    return (i);
}

int door_is_valid(t_data *data, char **map, int x, int y)
{
    int calc[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int type = 0;
    int i = 0;
    int targ_x, targ_y;
    int tmp;

    while (i < 4)
    {
        targ_x = calc[i][0] + x;
        targ_y = calc[i][1] + y;
        if (targ_x > data->map.w_map || targ_y > data->map.h_map  || targ_x < 0 || targ_y < 0)
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

    data->map.h_map = get_map_height(char_map);
    data->map.w_map = get_map_width(char_map);

    map = (t_cell **) malloc(data->map.h_map * sizeof(t_cell *));
    
    i = 0;
    while (i < data->map.h_map)
    {
        j = 0;
        map[i] = (t_cell *) malloc(data->map.w_map * sizeof(t_cell));
        while (j < data->map.w_map)
        {
            map[i][j].options = NULL;
            if (char_map[i][j] == 'D')
            {
                map[i][j].cell_type = DOOR;
                map[i][j].options = (t_door *) malloc (sizeof(t_door));
                ((t_door *)(map[i][j].options))->is_valid = door_is_valid(data, char_map, j, i);
                ((t_door *)(map[i][j].options))->is_open = false;
            }
            else if (char_map[i][j] == '1')
                map[i][j].cell_type = WALL;
            else if (char_map[i][j] == ' ')
                map[i][j].cell_type = NONE;
            else
                map[i][j].cell_type = SPACE;
            j++;
        }
        i++;
    }
    return (map);
}

// int main()
// {
//     char *diff = " 01D";
// char *map[] = {
//     "11111111111111111111111111",
//     "10000000000000000000000001",
//     "10100000010000000000000001",
//     "10100000100000D00000000001",
//     "10D00000000000000001D10001",
//     "101D1011000000000000100001",
//     "10100000000100000000000001",
//     "10000000000100000001000001",
//     "10000001000000000000000001",
//     "100000000000000000000000D1",
//     "11111111111111111111111111",
//     NULL
// };

//     t_data *data = malloc(sizeof(t_data));
//     data->map.map = create_map(data, map);
//     int i = 0, j = 0;

//     while (i < data->map.h_map)
//     {
//         j = 0;
//         while (j < data->map.w_map)
//         {
//             printf("%c", diff[data->map.map[i][j].cell_type]);
//             // printf("%d", data->map.map[i][j].cell_type);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
// }