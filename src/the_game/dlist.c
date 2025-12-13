/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:24:15 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/13 21:25:22 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_dlist	*new_dnode(t_door *door)
{
	t_dlist	*node;

	node = calloc(1, sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->door = door;
	node->next = NULL;
	return (node);
}

void	append_dnode(t_dlist **head, t_dlist *node)
{
	if (head == NULL)
		return ;
	if (*head != NULL)
		node->next = *head;
	*head = node;
}

void	append_door(t_dlist **head, t_door *door)
{
	t_dlist	*node;

	node = new_dnode(door);
	if (node == NULL)
		return ;
	append_dnode(head, node);
}

void	clear_dlist(t_dlist **head)
{
	t_dlist	*tmp;
	t_dlist	*current;

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
