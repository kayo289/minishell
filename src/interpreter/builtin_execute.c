#include "../../includes/minishell.h"

int builtin_execute(t_args args, t_shell *shell)
{
	if (ft_strcmp((*args)[0], "cd") == 0)
		cd(*args);
	else if (ft_strcmp((*args)[0], "echo") == 0)
		echo(*args);
	else if (ft_strcmp((*args)[0], "pwd") == 0)
		pwd(*args);
	else if (ft_strcmp((*args)[0], "unset") == 0)
		unset(*args, shell);
	else
		return (0);
	return (1);
}
