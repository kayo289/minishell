#include "../../includes/queue.h"

void	enq(t_queue *this, void *value)
{
	ft_lstadd_back(this, ft_lstnew(value));
}
