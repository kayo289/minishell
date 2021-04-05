#include "../../includes/minishell.h"

void unset(int argc, char **argv)
{
	int i;

	if (argc <= 1)
		return ;
	while (argv[i])
	{
		ft_unsetenv(argv[i]);
		i++;
	}
}
