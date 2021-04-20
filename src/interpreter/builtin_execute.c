#include "../../includes/minishell.h"

int builtin_execute(t_args args, t_shell *shell)
{
	if (ft_strcmp((*args)[0], "cd") == EQUAL)
		cd(*args);
	else if (ft_strcmp((*args)[0], "echo") == EQUAL)
		echo(*args);
	else if (ft_strcmp((*args)[0], "pwd") == EQUAL)
		pwd(*args);
	else if (ft_strcmp((*args)[0], "unset") == EQUAL)
		unset(*args, shell);
	else
		return (UNEXEC);
	return (EXEC);
}
