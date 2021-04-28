#include "../../includes/minishell.h"

static void show_env(void)
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
	if (argv[1] == NULL && argc == 1)
		show_env();
	return (0);
}
