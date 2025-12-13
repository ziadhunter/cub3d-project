#ifndef DOOR_H
#define DOOR_H

#include <cub3d.h>
#include <ray_cast.h>

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

typedef struct s_dlist
{
    t_door *door;
    struct s_dlist *next;
} t_dlist;

t_dlist *new_dnode(t_door *door);
void    append_dnode(t_dlist **head, t_dlist *node);
void    append_door(t_dlist **head, t_door *door);
void    clear_dlist(t_dlist **head);

double	find_hy_intersection(t_data *data);
double	find_hx_intersection(t_data *data, t_ray *ray, double y_inter);
double	find_vy_intersection(t_data *data, t_ray *ray, double x_inter);
double	find_vx_intersection(t_data *data);
bool	is_dwall(t_data *data, t_ray_info ray_info, t_direction *intr,
		int intersection_type);

void door_check_using_rays(t_data *data);
void update_door_state(t_data *data);
void update_all_doors_state(t_dlist *head);

#endif