#include "../../includes/queue.h"

void *deq(t_queue *this)
{
	//t_list *tmp;
	t_list *top;

	if (*this == NULL)
		return (NULL);
	top = (*this)->tail->next;
	(*this)->tail = (*this)->tail->next;
	return (top->content);
}
