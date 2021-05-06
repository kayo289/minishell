#include "../../includes/minishell.h"

void exit_err(char *msg)
{
	err_cstmmsg("exit", msg);
	exit(255);
}

int minishell_exit(char **argv, t_shell *shell)
{
	int i;
	long int n;
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
			minus = -1;
			i++;
		}
		n = 0;
		while (argv[1][i] != '\0')
		{
			if (ft_isdigit(argv[1][i]))
			{
				n = n * 10 + (argv[1][i] - '0');
				if (n * minus > INT_MAX || n * minus < INT_MIN)
					exit_err("numeric argument required");
			}
			else
				exit_err("numeric argument required");
			i++;
		}
		shell->exit_status = n * minus;
	}
	exit(shell->exit_status);
	return (0);
}
