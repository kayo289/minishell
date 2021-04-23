#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	new = ft_lstnew((*f)(lst->content));
	if (!lst || !new)
		return (NULL);
	tmp = new;
	lst = lst->next;
	while (lst)
	{
		tmp->next = ft_lstnew((f)(lst->content));
		if (!tmp->next)
			ft_lstclear(&new, del);
		tmp = tmp->next;
	}
	return (new);
}
