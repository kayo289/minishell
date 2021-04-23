#include "../../includes/libft.h"

void	ft_dlstinsert(t_dlist **lst, t_dlist *new)
{
	if (*lst == NULL)
		return ;
	if ((*lst)->next == NULL)
		ft_dlstadd_back(lst, new);
	else
	{
		new->next = (*lst)->next;
		new->prev = (*lst);
		(*lst)->next->prev = new;
		(*lst)->next = new;
	}
}
