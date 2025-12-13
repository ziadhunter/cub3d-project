#ifndef DB_COLLECTOR_H
#define DB_COLLECTOR_H

#include <libft.h>

void	appendlist_to_gbcollector(t_list *node);
void	free_all(void);
void	save_ptr(void *data);
void	*ft_smalloc(unsigned long size);

#endif