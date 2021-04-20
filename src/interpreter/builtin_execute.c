#include "../../includes/minishell.h"

int builtin_execute(t_args args, t_shell *shell)
{
	if (ft_strcmp((*args)[0], "cd") == EQUAL)
		minishell_cd(*args);
	else if (ft_strcmp((*args)[0], "echo") == EQUAL)
		minishell_echo(*args);
	else if (ft_strcmp((*args)[0], "pwd") == EQUAL)
		minishell_pwd(*args);
	else if (ft_strcmp((*args)[0], "unset") == EQUAL)
		minishell_unset(*args, shell);
	else if (ft_strcmp((*args)[0], "exit") == EQUAL)
		minishell_exit(*args, shell);
	else
		return (UNEXEC);
	return (EXEC);
}
