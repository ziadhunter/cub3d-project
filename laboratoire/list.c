#include "cub.h"

t_list *new_node(t_door *door)
{
    t_list *node;

    node = calloc(1, sizeof(t_list));
    if (node == NULL)
        return (NULL);
    node->door = door;
    node->next = NULL;
    return (node);
}

void append_node(t_list **head, t_list *node)
{
    if (head == NULL)
        return ;
    if (*head != NULL)
        node->next = *head;
    *head = node;
}

void append_door(t_list **head, t_door *door)
{
    t_list *node;

    node = new_node(door);
    if (node == NULL)
        return ;
    append_node(head, node);
}

void clear_list(t_list **head)
{
    t_list *tmp, *current;

    if (head == NULL)
        return ;
    current = *head;
    while (current)
    {
        tmp = current;
        current = current->next;
        free(tmp->door);
        free(tmp);
    }
}