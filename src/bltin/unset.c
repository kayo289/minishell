#include "../../includes/minishell.h"

static void del_shell_var(t_shell *this, char *name)
{
	t_list	*top;
	t_list	*prev;
	char	*var;
	int		h;

	h = hash(name);
	top = this->var[h];
	prev = NULL;
	while (top != NULL)
	{
		var = get_param_name((char *)top->content);
		if (ft_strcmp(var, name) == EQUAL)
		{
			if (prev == NULL)
				this->var[h] = top->next;
			else
				prev->next = top->next;
			ft_lstdelone(top, free);
			free(var);
			return;
		}
		free(var);
		prev = top;
		top = top->next;
	}
}

int is_notssnack_case(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_issnack_case(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int minishell_unset(char **argv, t_shell *shell)
{
	int i;
	int status;

	status = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_isdigit(*argv[i]) || is_notssnack_case(argv[i]) || ft_unsetenv(argv[i]) < 0)
		{
			err_cstmmsg("unset", argv[i], "not a valid identifier");
			status = 1;
		}
		del_shell_var(shell, argv[i]);
		i++;
	}
	return (status);
}
