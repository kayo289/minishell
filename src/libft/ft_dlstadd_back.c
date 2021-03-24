#include "../../includes/libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	if (*lst)
		ft_dlstlast(*lst)->next = new;
	else
		*lst = new;
}
