/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collector.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:28:23 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/17 16:28:24 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DB_COLLECTOR_H
# define DB_COLLECTOR_H

# include <libft.h>

void	appendlist_to_gbcollector(t_list *node);
void	free_all(void);
void	save_ptr(void *data);
void	*ft_smalloc(unsigned long size);

#endif