#include "../includes/minishell.h"

#define MESSAGE1 "syntax error near unexpected token " 
#define MESSAGE2 ": command not found"

// issue #64 search execute file form PATH
char **fetch_path(char ****args)
{
	char **path;
	// fetch absolute path from PATH.
	//ex)
	// cat	-> /bin/cat
	// head -> /usr/bin/cat
	// grep -> /bin/cat
	// return ({/bin/grep, /usr/bin/head, /bin/cat, NULL});

	// === dummy ===
	int i;
	for (i = 0; (*args)[i] != NULL; i++)
	path = (char **)malloc (sizeof(char *) * i);
	for (i = 0; (*args)[i] != NULL; i++)
		path[i] = ft_strdup((*args)[i][0]);
	// === dummy ===
	return (path);
}

void error(char *message, char *token)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(token, 2);
	exit(1);
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
			get_token(line, ip);
			if (ip->sy == IDENTIFY)
			{
				exe_cmd(0, *args, fetch_path(args));
				free(*args);
				input(line, ip, args);
			}
			else if (ip->sy != INPUT_END)
				error(MESSAGE1, ip->id_string);
		}
		else if (ip->sy == INPUT_END)
			exe_cmd(0, *args, fetch_path(args));
	}
	else if (ip->sy != INPUT_END)
		error(MESSAGE1, ip->id_string);
}

void command(char **line, t_ip *ip, char ****args)
{
	const char *cmds[] =
		{"cd", "echo", "pwd", "env", "export", "unset", "exit", NULL};
	char **arg;
	int i;

	i = 0;
	arg = (char**)ft_calloc2(sizeof(char*), 1);
	while (cmds[i] != NULL)
	{
		if (equal((char*)cmds[i], ip->id_string))
			break;
		i++;
	}
	if (cmds[i] == NULL)
		error(*line, MESSAGE2);
	else
	{
		while (ip->sy == IDENTIFY)
		{
			arg = ft_realloc2(arg, ip->id_string);
			get_token(line, ip);
		}
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
