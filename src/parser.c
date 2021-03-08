#include "../includes/minishell.h"

#define MESSAGE1 "syntax error near unexpected token " 
#define MESSAGE2 ": command not found"

// issue #64 search execute file form PATH
char *get_env_value(char *key)
{
	extern char **environ;
	char **str;
	char  *value;
	int	i;
	int j;

	value = (char *)ft_calloc(sizeof(char), 1);
	i = 0;
	while (environ[i] != NULL) 
	{
		str = ft_split(environ[i], '=');
		if (equal(str[0], key) == true)
		{
			j = 1;
			while (str[j] != NULL)
			{
				value = ft_strjoin(value, str[j]);
				j++;
			}
		}
		i++;
	}
	return (value);
}

bool find_command(char *cmd, char ***cmd_paths, char **dir_names)
{
	int				i;
	DIR				*dir;
	struct dirent	*dp;
	struct stat		sb;
	char			*cmd_path;

	i = -1;
	while (dir_names[++i] != NULL)
	{
		if ((dir = opendir(dir_names[i])) == NULL)
			continue;
		while ((dp = readdir(dir)) != NULL)
		{
			if (lstat(dp->d_name, &sb) > 0)
				continue;
			if (S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode))
			{
				if (equal(cmd, dp->d_name))
				{
					cmd_path = ft_strjoin("/", dp->d_name);
					cmd_path = ft_strjoin(dir_names[i], cmd_path);
					*cmd_paths = ft_realloc2(*cmd_paths, cmd_path); 
					return (true);
				}
			}
		}
		closedir(dir);
	}
	return (false);
}

char **fetch_path(char ****args)
{
	// fetch absolute path from PATH.
	//ex)
	// cat	-> /bin/cat
	// head -> /usr/bin/cat
	// grep -> /bin/cat
	// return ({/bin/grep, /usr/bin/head, /bin/cat, NULL});

	char	*env_value;
	char	**dir_names;
	char	**cmd_paths;
	int 	i;

	env_value = get_env_value("PATH");
	dir_names = ft_split(env_value, ':');
	cmd_paths = (char **)ft_calloc2(sizeof(char *), 1);
	i = 0;
	while ((*args)[i] != NULL)
	{
		if (!find_command((*args)[i][0], &cmd_paths, dir_names))
			error((*args)[i][0], MESSAGE2);
		i++;
	}
	return (cmd_paths);
}

void error(char *message, char *token)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(token, 2);
	exit(1);
}

void go_exe_cmd(char ****args)
{
	pid_t pid;
	int status;

	if ((pid = fork()) == 0)
		exe_cmd(0, *args, fetch_path(args));
	else
	{
		waitpid(pid, &status, 0);
		free(*args);
	}
}

void input(char **line, t_ip *ip, char ****args)
{
	if (ip->sy == IDENTIFY)
	{
		command(line, ip, args);
		while (ip->sy == GT || ip->sy == LT || ip->sy == DGT)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY) 
				get_token(line, ip);
			else
				error(MESSAGE1, ip->id_string);
		}
		if (ip->sy == PIPE)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY)
				input(line, ip, args);
			else
				error(MESSAGE1, ip->id_string);
		}
		if (ip->sy == SEMICOLON)
		{
			go_exe_cmd(args);
			get_token(line, ip);
			if (ip->sy == IDENTIFY)
			{
				*args = ft_calloc3(sizeof(char **), 1);
				input(line, ip, args);
			}
			else if (ip->sy != INPUT_END)
				error(MESSAGE1, ip->id_string);
		}
		else if (ip->sy == INPUT_END)
			go_exe_cmd(args);
	}
	else if (ip->sy != INPUT_END)
		error(MESSAGE1, ip->id_string);
}

void command(char **line, t_ip *ip, char ****args)
{
	char **arg;

	arg = (char**)ft_calloc2(sizeof(char*), 1);
	while (ip->sy == IDENTIFY)
	{
		arg = ft_realloc2(arg, ip->id_string);
		get_token(line, ip);
	}
	*args = ft_realloc3(*args, arg);
	return;
}

char  **ft_realloc2(char **old, char *add)
{
	char **new;
	int len;
	int i;

	len = 0;
	while (old[len] != NULL)
		len++;
	new = (char**)malloc(sizeof(char*) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = old[i]; 
		i++;
	}
	new[i++] = add;
	new[i] = NULL;
	return (new);
}

char  ***ft_realloc3(char ***old, char **add)
{
	char ***new;
	int len;
	int i;
	int j;

	len = 0;
	while (old[len] != NULL)
		len++;
	new = (char***)malloc(sizeof(char**) * (len + 2));
	new[0] = add;
	i = 0;
	j = 1;
	while (old[i] != NULL)
		new[j++] = old[i++]; 
	new[j] = NULL; 
	return (new);
}

char  **ft_calloc2(size_t nmemb, size_t size)
{
	char **ret;
	size_t i;

	ret = (char**)malloc(nmemb * size);
	i = 0;
	while (i < size)
	{
		ret[i] = NULL;
		i++;
	}
	return (ret);
}

char  ***ft_calloc3(size_t nmemb, size_t size)
{
	char ***ret;
	size_t i;

	ret = (char***)malloc(nmemb * size);
	i = 0;
	while (i < size)
	{
		ret[i] = NULL;
		i++;
	}
	return (ret);
}
