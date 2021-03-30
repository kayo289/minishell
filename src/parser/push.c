#include "../../includes/minishell.h"

void push(char *str, t_queue *queue)
{
	t_list *lst;
	char *s;
	
	s = ft_strdup(str);
	lst = ft_lstnew(s);
	ft_lstadd_back(queue, lst);
}

