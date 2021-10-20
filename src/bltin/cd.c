#include "../../includes/minishell.h"

char *get_home_path(char **argv)
{
	char *path;

	if (argv[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			err_cstmmsg("cd", NULL, "HOME not set");
			return (NULL);
		}
		return (path);
	}
	return (argv[1]);
}

char *get_parent(char *path)
{
	char *result;

	result = ft_substr(path, 0, ft_strrchr(path, '/') - path);
	if (result && ft_strlen(result) == 0)
		result = ft_strdup("/");
	return (result);
}

void set_pwd(char *new_path, t_shell *shell)
{
	char *param;
	char *set_path;
	char *pwd;

	pwd = getenv("PWD");
	if (pwd == NULL || ft_strcmp(pwd, "") == 0)
		param = ft_strjoin("OLDPWD=", "");
	else
		param = ft_strjoin("OLDPWD=", shell->pwd);
	set_shell_var(shell, param);
	free(param);

	set_path = ft_strdup(new_path);
	param = ft_strjoin("PWD=", new_path);
	set_shell_var(shell, param);
	free(param);
	free(shell->pwd);
	shell->pwd = set_path;
	//free(set_path);
}

int change_dir(char *path, t_shell *shell)
{
	char *absolute_path;
	char *change_path;
	bool is_absolute_path;
	char *getcwd_path;

	absolute_path = get_absolute_path(path, &is_absolute_path, shell);
	if (chdir(absolute_path) == 0)
	{
		getcwd_path = getcwd(NULL, 0);
		if (!getcwd_path)
			ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		if (is_absolute_path == false)
			absolute_path = getcwd_path;
		set_pwd(absolute_path, shell);
		free(absolute_path);
		free(getcwd_path);
		return (0);
	}

	if (chdir(path) == 0)
	{
		getcwd_path = getcwd(NULL, 0);
		if (!getcwd_path)
			ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		change_path = getcwd_path;
		if (change_path == NULL)
			change_path = absolute_path;
		set_pwd(change_path, shell);
		free(absolute_path);
		free(getcwd_path);
		return (0);
	}
	free(absolute_path);
	return (1);
}


int use_cdpath_chg(char **argv, char *path, t_shell *shell)
{
	char *cdpath;
	char **str;
	int  i;
	char *tmp;

	i = 0;
	if (argv[1] == NULL
	|| ft_strcmp(path, ".") == 0
	|| ft_strcmp(path, "..") == 0
	|| argv[1][0] == '/'
	|| ft_strncmp(path, "./", 2) == 0
	|| ft_strncmp(path, "../", 3) == 0
	|| getenv("CDPATH") == NULL)
		return (FALSE);
	if (getenv("CDPATH")[0] == ':')
		tmp = ft_strjoin(".",getenv("CDPATH"));
	else
		tmp = ft_strdup(getenv("CDPATH"));
	str = ft_split(tmp, ':');
	free(tmp);
	while(str[i])
	{
		if (str[i][0] == '/')
			cdpath = path_join(str[i], path);
		else
			cdpath = three_path_join(shell->pwd, str[i], path);
		if (change_dir(cdpath, shell) == 0)
		{
			if (!(str[i][0] == '.' && str[i][1] == '\0'))
				ft_putendl_fd(shell->pwd, 1);
			dp_free(str);
			free(cdpath);
			return (TRUE);
		}
		free(cdpath);
		i++;
	}
	dp_free(str);
	return (FALSE);
}

int minishell_cd(char **argv, t_shell *shell)
{
	char *new_path;
	int status;

	if (!shell->pwd)
		shell->pwd = getcwd(NULL, 0);
	new_path = get_home_path(argv);
	if (ft_strcmp(new_path, "") == EQUAL)
		return (0);
	if (new_path == NULL)
		return (1);
	if (use_cdpath_chg(argv, new_path, shell))
		return (0);
	status = change_dir(new_path, shell);
	if (status == 0)
		return (0);
	err_errno("cd", new_path);
	return (1);
}
