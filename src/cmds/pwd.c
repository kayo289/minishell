#include "../../includes/minishell.h"

int main(int argc, char **argv)
{
	char *path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, 1);
	return (0);
	(void)argc;
	(void)argv;
}
