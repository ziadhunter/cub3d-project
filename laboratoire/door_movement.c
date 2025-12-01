#include "cub.h"

void update_all_doors_state(t_list *head)
{
    // static bool is_printing = false;
    t_door *door;
    while (head)
    {
        door = head->door;
        if (door->door_state == CLOSING)
        {
            // if (is_printing == false)
            //     write(1, "door closing ", 14), is_printing = true;
            // write(1, ".", 1);
            if (door->door_position++ >= TILE_SIZE)
                door->door_state = CLOSED; // , write(1, "\n", 1), is_printing = false;
        }
        else if (door->door_state == OPENING)
        {
            // if (is_printing == false)
            //     write(1, "door opening ", 14), is_printing = true;
            // write(1, ".", 1);
            if (door->door_position-- <= 0)
                door->door_state = OPENED; //, write(1, "\n", 1), is_printing = false;
        }
        head = head->next;
    }
}