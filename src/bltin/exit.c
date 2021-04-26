#include "../../includes/minishell.h"

int minishell_exit(char **argv, t_shell *shell)
{
	int i;
	int n;

	ft_putendl_fd("exit", 1);
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
		n = 0;
		i = -1;
		while (argv[1][++i] != '\0')
		{
			if (ft_isdigit(argv[1][i]))
				n = n * 10 + (argv[1][i] - '0');
			else
			{
				ft_putendl_fd("exit: numeric arguments required", 2);
				n = 255;
				break;
			}
		}
		(*shell)->exit_status = n;
	}
	exit((*shell)->exit_status);
	return (0);
}
