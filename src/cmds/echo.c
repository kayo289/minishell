#include "../../includes/minishell.h"

static void output(int pos, int argc, char **argv)
{
	if (pos + 1 >= argc)
	{
		ft_putstr_fd(argv[pos], 1);
		return;
	}
	ft_putstr_fd(argv[pos], 1);
	ft_putstr_fd(" ", 1);
	output(pos + 1, argc, argv);
}

int main(int argc, char **argv)
{
	if (argc <= 1 || ft_strcmp(argv[1], "-n") != 0)
	{
		output(1, argc, argv);
		ft_putendl_fd("", 1);
	}
	else
		output(2, argc, argv);
	exit(0);
}
