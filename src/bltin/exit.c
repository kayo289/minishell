#include "../../includes/minishell.h"

int minishell_exit(char **argv, t_shell *shell)
{
	int i;

	ft_putendl_fd("exit", 1);
	if (argv[1] != NULL)
	{
		i = -1;
		while (argv[1][++i] != '\0')
		{
			if (!ft_isdigit(argv[1][i]))
			{
				ft_putendl_fd("exit: numeric arguments required", 2);
				exit(255);
			}
		}
		if (argv[2] == NULL)
			exit(ft_atoi(argv[1]));
		else
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
	}
	exit((*shell)->exit_status);
	return (0);
}
