#include "../../includes/libft.h"

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	if (lst == NULL)
		return;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	(*del)(lst->content);
	free(lst);
}
