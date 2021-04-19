#include "../../includes/libcmds.h"

static int hash(char *name)
{
	int i;
	int h;

	h = 0;
	i = 0;
	while (name[i] != '\0')
	{
		h = h * 10 + name[i];
		h %= SIZE;
		i++;
	}
	return (h);
}

static char *del_shell_var(t_shell this, char *name)
{
	t_list *top;
	t_list *tmp;
	int h;

	h = hash(name);
	top = this->var[h];
	while (top->next != NULL && ft_strcmp(((t_param*)top->next->content)->key, name) != 0)
		top = top->next;
	if (top->next == NULL)
		return (NULL);
	tmp = top->next;
	top->next = tmp->next;
	free(tmp);
	return (NULL);
}

void unset(char **argv, t_shell *shell)
{
	if (argv[1])
		ft_unsetenv(argv[1]);
	del_shell_var(*shell, argv[1]);
}
