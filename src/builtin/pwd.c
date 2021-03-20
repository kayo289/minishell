#include "../../includes/minishell.h"

void pwd(int argc, char **argv)
{
	char *path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, 1);
	(void)argc;
	(void)argv;
}
