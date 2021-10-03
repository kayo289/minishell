#include "../../includes/minishell.h"

bool lookup_bltin(char **args)
{
	const char *bltin_name[] = {
		"cd", "echo", "pwd", "unset", "exit", "export", "env", NULL\
	};
	int i;

	i = 0;
	while (bltin_name[i] != NULL)
	{
		if (ft_strcmp(args[0], bltin_name[i]) == EQUAL)
			return (true);
		i++;
	}
	return (false);
}

void execute_bltin(char **args, t_shell *shell)
{
	int n;
	
	n = shell->exit_status;
	if (ft_strcmp(args[0], "cd") == EQUAL)
		n = minishell_cd(args, shell);
	else if (ft_strcmp(args[0], "echo") == EQUAL)
		n = minishell_echo(args);
	else if (ft_strcmp(args[0], "pwd") == EQUAL)
		n = minishell_pwd(args);
	else if (ft_strcmp(args[0], "unset") == EQUAL)
		n = minishell_unset(args, shell);
	else if (ft_strcmp(args[0], "exit") == EQUAL)
		n = minishell_exit(args, shell);
	else if (ft_strcmp(args[0], "export") == EQUAL)
		n = minishell_export(args, shell);
	else if (ft_strcmp(args[0], "env") == EQUAL)
		n = minishell_env(args);
	shell->exit_status = n;
}
