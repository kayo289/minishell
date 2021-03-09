#include "../includes/minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

static int ft_setenv(char *name, char *value)
{
	extern char **environ;
	char **str;
	char *tmp;
	int i;

	i = 0;
	if (name == NULL || ft_strchr(name, '=') != NULL)
		return (-1);
	tmp = ft_strjoin(name, "=");
	tmp = ft_strjoin(tmp, value);
	while (environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (equal(str[0], name) == true)
		{
			environ[i] = tmp;
			return (0);
		}
		i++;
	}
	environ[i] = ft_strdup(tmp);
	return (0);
}

int main(int argc, char **argv)
{
	char *path;
	char *old_path;

	old_path = getcwd(NULL, 0);
	if (argc == 1)
		path = get_env_value("HOME");
	else
		path = argv[2];
	if (chdir(path) != 0)
		ft_putstr_fd("cd: no such file or directory", 2);
	else
	{
		ft_setenv("OLDPWD", old_path);
		path = getcwd(NULL, 0);
		ft_setenv("PWD", path);
		free(path);
	}
	free(old_path);
	printf("現在地:%s\n", getcwd(NULL, 0));
	return (0);
}
