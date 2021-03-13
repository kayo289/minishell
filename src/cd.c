#include "../includes/minishell.h"

int main(int argc, char **argv)
{
	char *path;
	char *old_path;

	old_path = getcwd(NULL, 0);
	if (argc == 1)
		path = ft_getenv("HOME");
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	else
	{
		ft_setenv("OLDPWD", old_path);
		path = getcwd(NULL, 0);
		ft_setenv("PWD", path);
		free(path);
	}
	free(old_path);
	// printf("現在地:%s\n", getcwd(NULL, 0));
	return (0);
}
