#include "../../includes/minishell.h"

char *get_shell_var(t_shell *this, char *name)
{
	t_list	*top;
	int		h;

	h = hash(name);
	top = this->var[h];
	while (top != NULL)
	{
		if (ft_strncmp(top->content, name, ft_strlen(name)) == EQUAL)
			return ((char *)top->content);
		top = top->next;
	}
	return (NULL);
}

