#include "../../includes/libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (lst && new)
	{
		new->new = *lst;
		*lst = new;
	}
}
