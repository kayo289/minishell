#include "../../includes/libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist		*elem;

	elem = ft_dlstlast(*lst);
	if (*lst)
	{
		elem->next = new;
		new->prev = elem;
	}
	else
		*lst = new;
}
