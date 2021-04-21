#include "../../includes/queue.h"

void	enq(t_queue *this, void *value)
{
	t_list *lst;

	lst = ft_lstnew(value);
	this->head->next = lst;
	this->head = lst;
}
