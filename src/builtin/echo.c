#include "../../includes/libcmds.h"

static char check_opt_n(char ***argv)
{
	bool opt_n;
	int i;

	opt_n = false;
	while (**argv != NULL)
	{
		if (ft_strncmp(**argv, "-n", 2) != 0)
			return (opt_n);
		i = 2;
		while ((**argv)[i] != '\0')
			if ((**argv)[i++] != 'n')
				return (opt_n);
		opt_n = true;
		(*argv)++;
	}
	return (opt_n);
}

static void output(char **argv)
{
	if (*argv == NULL)
		return;
	ft_putstr_fd(*argv, 1);
	if (*(argv + 1) != NULL)
		ft_putstr_fd(" ", 1);
	output(argv + 1);
}

int minishell_echo(char **argv)
{
	bool opt_n;

	if (argv[1] == NULL)
	{
		ft_putendl_fd("", 1);
		return (1);
	}
	argv++;
	opt_n = check_opt_n(&argv);
	output(argv);
	if (opt_n == false)
		ft_putstr_fd("\n", 1);
	return (0);
}
