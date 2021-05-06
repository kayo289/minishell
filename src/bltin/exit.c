#include "../../includes/minishell.h"

void exit_err(char *s, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	exit(255);
}

int minishell_exit(char **argv, t_shell *shell)
{
	int i;
	long long int n;
	int minus;
	char *str;

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
		str = "";
		while (argv[1][i] != '\0')
		{
			str = ft_strjoin(str, &argv[1][i]);
			if (ft_isdigit(argv[1][i]))
			{
				if (n * minus <= (LLONG_MAX - (long long)(argv[1][i] - '0')) / 10 ||
					n * minus >= (LLONG_MIN - (long long)(argv[1][i] - '0')) / 10)
					n = n * 10 + (argv[1][i] - '0');
				else
					exit_err(str, "numeric argument required");
			}
			else
				exit_err(str, "numeric argument required");
			i++;
		}
		shell->exit_status = n * minus;
	}
	exit(shell->exit_status);
	return (0);
}
