#ifndef QUEUE_H
#define QUEUE

#include <stdio.h>
#include <stdbool.h>
#include "libft.h"

struct s_queue;
typedef struct s_queue t_queue;

struct s_queue
{
	t_list *	tail;
	t_list *	head;
};

void	enq(t_queue *this, void *value);
void	*deq(t_queue *this);
void	*front(t_queue *this);
int		q_size(t_queue *this);
bool	q_empty(t_queue *this);

#endif
