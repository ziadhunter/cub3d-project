#ifndef LIST_H
#define LIST_H

#include <door.h>
// #include <cub3d.h>

typedef struct s_dlist
{
    t_door *door;
    struct s_dlist *next;
} t_dlist;

t_dlist *new_dnode(t_door *door);
void    append_dnode(t_dlist **head, t_dlist *node);
void    append_door(t_dlist **head, t_door *door);
void    clear_dlist(t_dlist **head);

#endif