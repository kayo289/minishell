#include "../../includes/minishell.h"

char *get_shell_var(t_shell *this, char *name)
{
	t_list	*top;
	char	*param_name;
	int		h;

	h = hash(name);
	top = this->var[h];
	while (top != NULL)
	{
		param_name = get_param_name((char *)top->content);
		if (ft_strcmp(param_name, name) == EQUAL)
		{
			free(param_name);
			return (get_param_value((char *)top->content));
		}
		free(param_name);
		top = top->next;
	}
	return (NULL);
}

