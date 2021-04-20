#include "../../includes/libcmds.h"

static void del_shell_var(t_shell this, char *name)
{
	t_list *top;
	t_list *prev;
	int h;

	h = hash(name);
	top = this->var[h];
	prev = NULL; 
	while (top != NULL) 
	{
		if (ft_strcmp(((t_param*)top->content)->key, name) == EQUAL)
		{
			if (prev == NULL)
				this->var[h] = top->next;
			else
				prev->next = top->next;
			ft_lstdelone(top, free);
			return;
		}
		prev = top;
		top = top->next;
	}
}

void minishell_unset(char **argv, t_shell *shell)
{
	while (*argv != NULL)
	{
		if (ft_unsetenv(*argv) < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			return;
		}
		del_shell_var(*shell, *argv);
		argv++;
	}
}
