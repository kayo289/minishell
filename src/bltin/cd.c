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

int change_dir(char *param, int *is_use_cdpath)
{
	char *new_path;
	char **str;
	int i;
	char *buf;

	i = 0;
	if (param != NULL && getenv("CDPATH") != NULL)
	{
		if (getenv("CDPATH")[0] == ':')
			str = ft_split(ft_strjoin(".", getenv("CDPATH")), ':');
		else
			str = ft_split(getenv("CDPATH"), ':');
		//printf("str[0]:%s]",str[0]);
		while(str[i] && ft_strcmp(str[i], ".") != EQUAL)
		{
			buf = ft_strjoin(str[i], "/");
			new_path = ft_strjoin(buf, param);
			//printf("[new_path:%s]",new_path);
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

int minishell_cd(char **argv, t_shell *shell)
{
	char *param;
	char *new_path;
	int cnt;
	int is_use_cdpath;

	is_use_cdpath = 0;
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
		new_path = argv[1];
	if (change_dir(new_path, &is_use_cdpath) == 0)
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
