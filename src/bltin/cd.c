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

char *path_join(char *path, char *new_path)
{
	char *result_path;
	char *tmp;

	if (ft_strlen(path) == 0 || path[ft_strlen(path) - 1] != '/')
	{
		tmp = ft_strjoin(path, "/");
		result_path = ft_strjoin(tmp, new_path);
	}else{
		result_path = ft_strjoin(path, new_path);
	}
	return (result_path);
}

char *three_path_join(char *s1, char *s2, char *s3)
{
	char *str;
	char *str2;

	str = path_join(s1, s2);
	str2 = path_join(str, s3);
	return (str2);
}

char *get_parent(char *path)
{
	char *result;

	result = ft_substr(path, 0, ft_strrchr(path, '/') - path);
	if (result && ft_strlen(result) == 0)
	{
		result = ft_strdup("/");
	}
	return (result);
}

char *normalize(char *path)
{
	char **str;
	int i;
	char *result;
	struct stat buf;

	i = 0;
	str = ft_split(path, '/');
	result = ft_strdup("/");
	while (str[i])
	{
		if (ft_strncmp(str[i], "..", 2) == 0)
		{
			result = get_parent(result);
		}else if (str[i][0] != '.'){
			result = path_join(result, str[i]);
		}
		if (stat(result, &buf) != 0)
			return (NULL);
		i++;
	}
	if (ft_strlen(result) == 0)
		result = ft_strdup("/");
	if (path[0] == '/' && path[1] == '/' && path[2] != '/')
		result = path_join("/", result);
	return (result);
}

char *get_absolute_path(char *path, bool *is_absolute_path)
{
	char *new_path;
	char *norm_path;

	if(path[0] == '/')
		new_path = path;
	else
		new_path = path_join(getenv("PWD"), path);
	norm_path = normalize(new_path);
	if (norm_path != NULL)
	{
		*is_absolute_path = true;
		return (norm_path);
	}
	*is_absolute_path = false;
	return (new_path);
}

void set_pwd(char *new_path, t_shell *shell)
{
	char *param;

	param = ft_strjoin("OLDPWD=", getenv("PWD"));
	set_shell_var(shell, param);

	param = ft_strjoin("PWD=", new_path);
	set_shell_var(shell, param);
}

int change_dir(char *path, t_shell *shell)
{
	char *absolute_path;
	char *change_path;
	bool is_absolute_path;
	
	absolute_path = get_absolute_path(path, &is_absolute_path);
	if (chdir(absolute_path) == 0)
	{
		if (!getcwd(NULL, 0))
			ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		if (is_absolute_path == false)
			absolute_path = getcwd(NULL, 0);
		set_pwd(absolute_path, shell);
		return (0);
	}

	if (chdir(path) == 0)
	{
		if (!getcwd(NULL, 0))
			ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		change_path = getcwd(NULL, 0);
		if (change_path == NULL)
			change_path = absolute_path;
		set_pwd(change_path, shell);
		return (0);
	}
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
		tmp = getenv("CDPATH");
	str = ft_split(tmp, ':');
	while(str[i])
	{
		if (str[i][0] == '/')
			cdpath = path_join(str[i], path);
		else
			cdpath = three_path_join(getenv("PWD"), str[i], path);
		if (change_dir(cdpath, shell) == 0)
		{
			if (!(str[i][0] == '.' && str[i][1] == '\0'))
				ft_putendl_fd(getenv("PWD"), 1);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int minishell_cd(char **argv, t_shell *shell)
{
	char *new_path;
	int status;

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
