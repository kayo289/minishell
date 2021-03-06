#include "../../includes/minishell.h"

int main(int argc, char **argv)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
	(void)argc;
	(void)argv;
}
