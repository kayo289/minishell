#ifndef QUEUE_H
# define QUEUE_H

# include <stdio.h>
# include <stdbool.h>
# include "libft.h"

typedef t_list	*t_queue;

void	enq(t_queue *this, void *value);
void	*deq(t_queue *this);
void	*front(t_queue *this);
int		q_size(t_queue *this);
bool	q_empty(t_queue *this);

#endif
