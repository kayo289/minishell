#include "../../includes/minishell.h"

static void show_env(void)
{
	extern char **environ;
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strchr(environ[i], '=') != NULL)
		ft_putendl_fd(environ[i], 1);
		i++;
	}
}

int minishell_env(char **argv)
{
	if (argv[1] == NULL)
		show_env();
	return (0);
}
