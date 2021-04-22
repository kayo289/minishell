#include "../../includes/queue.h"

void	enq(t_queue *this, void *value)
{
	t_list *lst;

	lst = ft_lstnew(value);
	if (*this == NULL)
	{
		*this = malloc(sizeof(t_queue));
		(*this)->tail = ft_lstnew(NULL);
		(*this)->tail->next = lst;
		(*this)->head = lst;
	}
	else
	{
		(*this)->head->next = lst;
		(*this)->head = lst;
	}
}
