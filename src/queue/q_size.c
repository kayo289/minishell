#include "../../includes/queue.h"

int	q_size(t_queue *this)
{
	return (ft_lstsize((*this)));
}
