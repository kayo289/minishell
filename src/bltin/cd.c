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

int change_dir2(char *param, int *is_use_cdpath)
{
	char *new_path;
	char **str;
	int i;
	char *buf;

	i = 0;
	if (param != NULL && param[0] != '.' && getenv("CDPATH") != NULL)
	{
		if (getenv("CDPATH")[0] == ':')
			str = ft_split(ft_strjoin(".", getenv("CDPATH")), ':');
		else
			str = ft_split(getenv("CDPATH"), ':');
		while(str[i] && ft_strcmp(str[i], ".") != EQUAL)
		{
			buf = ft_strjoin(str[i], "/");
			new_path = ft_strjoin(buf, param);
			if (param[0] != '/' && chdir(new_path) == 0)
			{
				*is_use_cdpath = 1;
				return (0);
			}
			i++;
		}
	}
	new_path = param;
	if (chdir(new_path) == 0)
		return (0);
	return (1);
}

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

char *ft_3strjoin(char *s1, char *s2, char *s3)
{
	char *str;
	char *str2;

	str = ft_strjoin(s1, s2);
	str2 = ft_strjoin(str, s3);
	return (str2);
}

/*
 * return absolute path
 */
char *get_absolute_path(char *path)
{
	char *new_path;

	if(path[0] == "/")
		new_path = path;
	else
		new_path = ft_strjoin(getenv("PWD"), path);
	// custom absolute path
	return (new_path);
}

int change_dir(char *path)
{
	char *new_path;

	new_path = get_absolute_path(path);
	//using chdir
	if (chdir(new_path) == 0)
	{
		//success
		//save pwd
		//save oldpwd
		return (0)
	}
	return (1);
}

int search_cdpath(char **argv, char *path)
{
	char *cdpath;
	char **s;
	int  i;

	i = 0;
	if (argv[1] == NULL 
	|| ft_strcmp(path, ".") == 0
	|| ft_strcmp(path, "..") == 0
	|| ft_strcmp(path, "/") == 0
	|| ft_strncmp(path, "./", 2) == 0
	|| ft_strncmp(path, "../", 3) == 0)
		return (FALSE);
	str = ft_split(getenv("CDPATH"), ':');
	while(str[i])
	{
		if (str[i][0] == "/")
			cdpath = ft_strjoin(str[i], path);
		else
			cdpath = ft_3strjoin(getenv("PWD"), str[i], path);
		if (change_dir(cdpath))
		{
			ft_putendl_fd(cdpath, 1);
			return (TRUE)
		}
		//free(cdpath);
		i++;
	}
	return (FLASE);
}

int minishell_cd(char **argv, t_shell *shell)
{
	char *param;
	char *new_path;
	int cnt;
	int is_use_cdpath;

	new_path = get_home_path(argv);
	if (ft_strcmp(new_path, "") == EQUAL)
		return (0);
	if (new_path == NULL)
		return (1);
	if (search_cdpath(argv, new_path))
		return (0);
	is_use_cdpath = 0;
	if (change_dir2(new_path, &is_use_cdpath) == 0)
	{
		if (is_use_cdpath == 0)
		{
			if (argv[1] == NULL)
				cnt = count_first_samestr(new_path, '/');
			else
				cnt = count_first_samestr(argv[1], '/');
			if(cnt == 2)
				new_path = argv[1];
			else
				new_path = getcwd(NULL, 0);
		}else{
			cnt = count_first_samestr(getenv("CDPATH"), '/');
			if (cnt <= 1)
				new_path = getcwd(NULL, 0);
			else if(cnt == 2)
				new_path = ft_strjoin("/", getcwd(NULL, 0));
			else
			{ 
				new_path = ft_strjoin(getenv("CDPATH"), new_path);
				new_path = &new_path[cnt - 1];
			}
			ft_putendl_fd(new_path, 1);
		}
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
