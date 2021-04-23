#include "../../includes/libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_dlstdelone(*lst, del);
		*lst = temp;
	}
}
