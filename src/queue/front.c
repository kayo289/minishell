#include "../../includes/queue.h"

void *front(t_queue *this)
{
	if (*this == NULL)
		return (NULL);
	return ((*this)->content);
}
