#include "cub.h"

void update_all_doors_state(t_list *head)
{
    t_door *door;
    while (head)
    {
        door = head->door;
        if (door->door_state == CLOSING)
        {
            if (door->door_position++ >= TILE_SIZE - 1)
                door->door_state = CLOSED;
        }
        else if (door->door_state == OPENING)
        {
            if (door->door_position-- <= 1)
                door->door_state = OPENED;
        }
        head = head->next;
    }
}