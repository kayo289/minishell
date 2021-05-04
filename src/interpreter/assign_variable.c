#include "../../includes/minishell.h"

void assign_variable(t_queue *vars, t_shell *shell)
{
	char *var;

	while (!q_empty(vars))
	{
		var = deq(vars);
		set_shell_var(shell, var);
	}
}

