#include "../../includes/libcmds.h"

static void del_shell_var(t_shell this, char *name)
{
	t_list *top;
	t_list *tmp;
	int h;

	h = hash(name);
	top = this->var[h];
	while (top->next != NULL) 
	{
		if (ft_strcmp(((t_param*)top->next->content)->key, name) != 0)
		{
			tmp = top->next;
			top->next = tmp->next;
			free(tmp);
			return;
		}
		top = top->next;
	}
}

void unset(char **argv, t_shell *shell)
{
	if (argv[1] == NULL)
		return;
	ft_unsetenv(argv[1]);
	del_shell_var(*shell, argv[1]);
}
