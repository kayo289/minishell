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

static int ft_isdigits(char *num)
{
	int i;

	i = 0;
	while(num[i] != '\0')
	{
		if (ft_isdigit(num[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int calc_intarg_n(char **argv)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while(argv[i] != NULL)
	{
		if(ft_isdigits(argv[i]) == 1)
			cnt++;
		i++;
	}
	return (cnt);
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
		if (calc_intarg_n(argv) > 1)
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
			str = "";
			str = ft_strjoin(str, argv[1]);
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
