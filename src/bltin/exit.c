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
	int i;

	ft_putendl_fd("exit", 2);
	if (argv[1] != NULL)
	{
		i = 1;
		if (ft_strcmp(argv[i], "--") == 0)
			i++;
		n = ft_atoi(argv[i]);
		if (errno == ERANGE || ft_isdigits(argv[i]) == 0)
			exit_err(argv[i], "numeric argument required");
		if (argv[i + 1])
		{
			err_cstmmsg("exit", NULL, "too many arguments");
			return (1);
		}
		shell->exit_status = n;
	}
	exit(shell->exit_status);
	return (0);
}
