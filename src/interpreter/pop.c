#include "../../includes/minishell.h"

char *pop(t_queue *queue)
{
	t_list *head;

	head = *queue;
	*queue = (*queue)->next;
	return ((char *)head->content);
}

