#include "../../includes/queue.h"

void *deq(t_queue *this)
{
	t_list *tmp;
	void *ret;

	if (*this == NULL)
		return (NULL);
	ret = front(this);
	tmp = *this;
	*this = (*this)->next;
	free(tmp);
	return (ret);
}
