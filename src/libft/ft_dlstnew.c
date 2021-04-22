#include "../../includes/libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*elem;

	elem = (t_dlist *)malloc(sizeof(t_dlist));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
