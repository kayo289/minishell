#include "../../includes/minishell.h"

static void assign_shell_var(t_queue *vars, t_shell *shell)
{
	while (*vars != NULL)
		set_shell_var(*shell, pop(vars));
}

void assign_variable(ip, tokens, shell)
		t_ip **ip; t_queue *tokens; t_shell *shell;
{
	t_queue vars;

	vars = NULL;
	while ((*ip)->sy == IDENTIFY)
	{
		if (ft_strchr((*ip)->id_string, '=') != NULL)
		{
			push((*ip)->id_string, &vars);
			next_token(ip, tokens);
			if ((*ip)->sy == INPUT_END)
				assign_shell_var(&vars, shell);
		}
		else
			return;
	}
}
