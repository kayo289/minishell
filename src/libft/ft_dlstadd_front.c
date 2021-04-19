#include "../../includes/libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (*lst != NULL)
	{
		while ((*lst)->prev != NULL)
			*lst = (*lst)->prev;
		(*lst)->prev = new;
		new->next = *lst;
	}
	*lst = new;
}
