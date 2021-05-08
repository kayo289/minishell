#include "../../includes/minishell.h"

#define LIMIT			(LLONG_MAX / 10)
#define POSITIVE_LAST_D	(LLONG_MAX % 10)

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
	long long n;
	long long last_d;
	int i;
	int j;
	int sign;

	ft_putendl_fd("exit", 2);
	if (argv[1] != NULL)
	{
		if (calc_intarg_n(argv) > 1)
		{
			err_cstmmsg("exit", "too many arguments");
			return (1);
		}
		j = 1;
		if (ft_strcmp(argv[j], "--") == 0)
			j++;
		sign = 1;
		last_d = POSITIVE_LAST_D;
		i = 0;
		if (argv[j][i] == '-')
		{
			sign = -1;
			last_d++;
			i++;
		}
		else if (argv[j][i] == '+')
			i++;
		n = 0;
		while (argv[j][i] != '\0')
		{
			if (ft_isdigit(argv[j][i]))
			{
				if (n >= LIMIT)
				{
					if (n > LIMIT || (argv[j][i] - '0') > last_d)
						exit_err(argv[j], "numeric argument required");
				}
				n = n * 10 + (argv[j][i] - '0');
			}
			else
				exit_err(argv[j], "numeric argument required");
			i++;
		}
		if (n - 1 == INT_MAX || n - 2 == INT_MAX)
			shell->exit_status = n - 1 - INT_MAX;
		else if (n > 255)
			shell->exit_status = 255;
		else
			shell->exit_status = n * sign;
	}
	exit(shell->exit_status);
	return (0);
}
