#include "../../includes/minishell.h"

int count_first_samestr(char *str, char target)
{
	int c;
	int i;

	c = 0;
	i = 0;
	while(str[i]!='\0')
	{
		if (target != str[i])
			return(c);
		c++;
		i++;
	}
	return (c);
}

int minishell_cd(char **argv, t_shell *shell)
{
	char *param;
	char *new_path;
	int cnt;

	if (argv[1] == NULL)
	{
		new_path = getenv("HOME");
		if (ft_strcmp(new_path, "") == EQUAL)
			return (0);
		if (new_path == NULL)
		{
			err_cstmmsg("cd", NULL, "HOME not set");
			return (1);
		}
	}
	else
	{
		new_path = argv[1];
	}
	if (argv[2] != NULL)
	{
		err_cstmmsg("cd", NULL, "too many arguments");
		return (1);
	}
	if (chdir(new_path) == 0)
	{
		if (argv[1] == NULL)
			cnt = count_first_samestr(new_path, '/');
		else
			cnt = count_first_samestr(argv[1], '/');
		if(cnt == 2)
			new_path = argv[1];
		else
			new_path = getcwd(NULL, 0);
	}
	else
	{
		err_errno("cd", new_path);
		return (1);
	}
	param = ft_strjoin("OLDPWD=", getenv("PWD"));
	set_shell_var(shell, param);
	free(param);

	param = ft_strjoin("PWD=", new_path);
	set_shell_var(shell, param);
	free(param);
	// free(old_path);
	return (0);
}
