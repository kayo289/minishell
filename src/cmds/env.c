#include "../../includes/minishell.h"

static void show_env()
{
	extern char **environ;
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_putendl_fd(environ[i], 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 1)
		show_env();
	return (0);
	(void)argv;
}
