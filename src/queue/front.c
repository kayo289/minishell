#include "../../includes/queue.h"

void *front(t_queue *this)
{
	return (this->tail->next->content);
}
