#include "../../includes/libcmds.h"
#include <stdio.h>

static int judge_hyphen(char **argv, t_shell *shell)
{
	if (argv[1][1] == '\0')
	{
		if (ft_getenv("OLDPWD") == NULL)
		{
			(*shell)->exit_status = 1;
			return (1);
		}
	} else if (argv[1][1] != '\0')
	{
		(*shell)->exit_status = 2;
		return (1);
	}
	return (0);
}

void minishell_cd(char **argv, t_shell *shell)
{
	char *path;
	char *old_path;

	old_path = getcwd(NULL, 0);
	if (argv[1] == NULL)
		path = ft_getenv("HOME");
	else if (argv[1][0] == '-')
	{
		if (judge_hyphen(argv, shell) == 1)
			return;
		path  = ft_getenv("OLDPWD");
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		return;
	}
	else
	{
		ft_setenv("OLDPWD", old_path);
		path = getcwd(NULL, 0);
		ft_setenv("PWD", path);
		free(path);
	}
	free(old_path);
	return;
}
