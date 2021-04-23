#include "../../includes/libft.h"

void	ft_dlstinsert(t_dlist **lst, t_dlist *new)
{
	if (*lst == NULL)
		*lst = new;
	else if ((*lst)->next == NULL)
	{
		(*lst)->next = new;
		new->prev = (*lst);
	}
	else
	{
		new->next = (*lst)->next;
		new->prev = (*lst);
		(*lst)->next->prev = new;
		(*lst)->next = new;
	}
}
