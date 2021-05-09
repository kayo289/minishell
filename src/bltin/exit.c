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
	char *n;
	int flag;

	i = 0;
	flag = 0;
	n = ft_strtrim(num, " ");
	if (num[i] == '+' || num[i] == '-')
		i++;
	while(n[i] != '\0')
	{
		if (ft_isdigit(n[i]) == 1)
			flag = 1;
		else
			return (0);
		i++;
	}
	free(n);
	return (flag);
}

int minishell_exit(char **argv, t_shell *shell)
{
	long long n;
	int sign;
	int j;

	ft_putendl_fd("exit", 2);
	if (argv[1] != NULL)
	{
		j = 1;
		// printf("----\n");
		if (ft_strcmp(argv[j], "--") == 0)
			j++;
		n = ft_atoi(argv[j]);
		if (n < 0)
			sign = -1;
		else
			sign = 1;
		n *= sign;
		if (errno == ERANGE || ft_isdigits(argv[j]) == 0)
			exit_err(argv[j], "numeric argument required");
		if (argv[j + 1])
		{
			err_cstmmsg("exit", "too many arguments");
			return (1);
		}
		if (n - 1 == INT_MAX || (n - 2 == INT_MAX && sign == 1))
			shell->exit_status = n - 1 - INT_MAX;
		else if (n == LLONG_MIN)
			shell->exit_status = 0;
		else if (n > 255 || sign == -1)
			shell->exit_status = 255;
		else
			shell->exit_status = n;
	}
	exit(shell->exit_status);
	return (0);
}
