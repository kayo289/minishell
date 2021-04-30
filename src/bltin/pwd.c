#include "../../includes/minishell.h"

int minishell_pwd(char **argv)
{
	char *path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, 1);
	(void)argv;
	return (0);
}
