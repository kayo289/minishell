#include "../../includes/queue.h"

void *front(t_queue *this)
{
	if (*this == NULL)
		return (this);
	return ((*this)->tail->next->content);
}
