#include "../../includes/minishell.h"

int minishell_cd(char **argv, t_shell *shell)
{
	char *param;
	char *new_path;
	char *old_path;

	old_path = getcwd(NULL, 0);
	if (argv[1] == NULL)
	{
		new_path = getenv("HOME");
		if (ft_strcmp(new_path, "") == EQUAL)
			return (0);
	}
	else
		new_path = argv[1];
	if (chdir(new_path) == 0)
		new_path = getcwd(NULL, 0);
	else
	{
		err_errno("cd", argv[1]);
		free(old_path);
		return (1);
	}
	param = ft_strjoin("PWD=", new_path);
	set_shell_var(shell, param);
	free(param);
	free(new_path);

	param = ft_strjoin("OLD_PWD=", old_path);
	set_shell_var(shell, param);
	free(param);
	free(old_path);

	return (0);
}
