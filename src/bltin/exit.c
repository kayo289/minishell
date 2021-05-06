#include "../../includes/minishell.h"

int minishell_exit(char **argv, t_shell *shell)
{
	int i;
	int n;
	int minus;

	ft_putendl_fd("exit", 2);
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			err_cstmmsg("exit", "too many arguments");
			return (1);
		}
		minus = 1;
		i = 0;
		if (argv[1][i] == '-')
		{
			i++;
			minus = -1;
		}
		n = 0;
		while (argv[1][i] != '\0')
		{
			if (ft_isdigit(argv[1][i]))
				n = n * 10 + (argv[1][i] - '0');
			else
			{
				err_cstmmsg("exit", "numeric arguments required");
				n = 255;
				break;
			}
			i++;
		}
		shell->exit_status = n * minus;
	}
	exit(shell->exit_status);
	return (0);
}
