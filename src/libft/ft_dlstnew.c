
#include "../../includes/libft.h"

t_dlist *ft_dlstnew(void *content)
{
	t_dlist *elem;

	if(!(elem = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
