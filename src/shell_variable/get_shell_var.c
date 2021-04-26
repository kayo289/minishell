#include "../../includes/minishell.h"

char *get_shell_var(t_shell this, char *name)
{
	t_list *top;
	char *key;
	int h;

	h = hash(name);
	top = this->var[h];
	while (top != NULL)
	{
		key = ((t_param*)top->content)->key;
		if (ft_strcmp(key, name) == 0)
			return (((t_param *)top->content)->value);
		top = top->next;
	}
	return (NULL);
}

