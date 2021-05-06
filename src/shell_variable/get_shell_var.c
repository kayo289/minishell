#include "../../includes/minishell.h"

char *get_shell_var(t_shell *this, char *name)
{
	t_list	*top;
	char	*var;
	int		h;

	h = hash(name);
	top = this->var[h];
	while (top != NULL)
	{
		var = get_param_name((char *)top->content);
		if (ft_strcmp(var, name) == EQUAL)
		{
			free(var);
			return ((char *)top->content);
		}
		free(var);
		top = top->next;
	}
	return (NULL);
}

