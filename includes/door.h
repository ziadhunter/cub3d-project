#ifndef DOOR_H
#define DOOR_H

typedef enum e_door_state
{
    OPENING,
    OPENED,
    CLOSED,
    CLOSING
} t_door_state;

typedef struct s_door
{
    bool is_valid;
    t_door_state door_state;
    int door_position;
} t_door;

#endif