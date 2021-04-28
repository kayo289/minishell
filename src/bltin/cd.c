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
		free(old_path);
		return (1);
	}
	path = getcwd(NULL, 0);
	ft_setenv("OLDPWD", old_path);
	ft_setenv("PWD", path);
	free(old_path);
	free(path);
	return (0);
}
