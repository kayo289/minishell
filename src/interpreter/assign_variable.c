#include "../../includes/minishell.h"

void assign_variable(t_list *datas, t_shell *shell)
{
	char *var;

	while (!q_empty(&((t_data*)datas->content)->vars))
	{
		var = deq(&((t_data*)datas->content)->vars);
		set_shell_var(*shell, var);
	}
}
