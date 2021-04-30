#include "../../includes/libft.h"

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
