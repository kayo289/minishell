#include "../../includes/minishell.h"

int minishell_pwd(char **argv)
{
	char *path;

	path = getcwd(NULL, 0);
	if (argv[1] != NULL)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		return (1);
	}
	if (path == NULL)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
