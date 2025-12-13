#include <gb_collector.h>


static t_list	**collector(void)
{
	static t_list	*head;

	return (&head);
}

void	free_all(void)
{
	t_list	**head;
	t_list	*cur;
	t_list	*next;

	head = collector();
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	save_ptr(void *data)
{
	t_list	**head;
	t_list	*node;

	node = ft_lstnew(data);
	if (node == NULL)
		return ;
	head = collector();
	ft_lstadd_front(head, node);
}

void	*ft_smalloc(unsigned long size)
{
	void	*mal;

	mal = malloc(size);
	if (mal == NULL)
		return (NULL);
	save_ptr(mal);
	return (mal);
}

void	appendlist_to_gbcollector(t_list *node)
{
	t_list	**gbcollector;
	t_list	*head;

	gbcollector = collector();
	head = *gbcollector;
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	else
		*gbcollector = node;
}
