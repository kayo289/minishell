#include "../../includes/libft.h"

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	if (lst == NULL)
		return;
	if (lst->prev != NULL && lst->next != NULL)
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	else if (lst->prev != NULL)
		lst->prev->next = NULL;
	else if (lst->next != NULL)
		lst->next->prev = NULL;
	(*del)(lst->content);
	free(lst);
}
