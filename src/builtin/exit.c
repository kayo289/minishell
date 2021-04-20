#include "../../includes/libcmds.h"

void minishell_exit(char **argv, t_shell *shell)
{
	int argc;
	int n;

	ft_putendl_fd("exit", 2);
	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	if (argc >= 3)
	{
		ft_putendl_fd("too many arguments", 2);
		n = 1;
	}
	else if (argc == 2)
		n = ft_atoi(argv[2]);
	else
		n = 0;
	(*shell)->exit_status = n;
	exit(n);
}
