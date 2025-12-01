#ifndef LIST_H
#define LIST_H

#include "door.h"
#include "cub.h"

typedef struct s_list
{
    t_door *door;
    struct s_list *next;
} t_list;

t_list *new_node(t_door *door);
void append_node(t_list **head, t_list *node);
void append_door(t_list **head, t_door *door);
void clear_list(t_list **head);

#endif