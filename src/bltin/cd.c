#include "../../includes/minishell.h"

int minishell_cd(char **argv)
{
	char *path;
	char *old_path;

	old_path = getcwd(NULL, 0);
	if (argv[1] == NULL)
		path = ft_getenv("HOME");
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	else
	{
		ft_setenv("OLDPWD", old_path);
		path = getcwd(NULL, 0);
		ft_setenv("PWD", path);
		free(path);
	}
	free(old_path);
	return (0);
}
