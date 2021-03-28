#include "../../includes/libft.h"

#include <stdio.h>
void	ft_dlstinsert(t_dlist **lst, t_dlist *new)
{
	t_dlist		*elem;

	if (*lst == NULL)
		return;
	elem = *lst;
	new->next = elem->next;
	new->prev = elem;
	elem->next->prev = new;
	elem->next = new;
}
