#include "../../includes/queue.h"

int	q_size(t_queue *this)
{
	if (*this == NULL)
		return (0);
	return (ft_lstsize((*this)->tail) - 1);
}
