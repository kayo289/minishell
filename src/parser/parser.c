#include "../../includes/minishell.h"

#define MESSAGE1 "syntax error near unexpected token " 
#define MESSAGE2 ": command not found"

static void go_exec_cmd(char ****args)
{
	pid_t pid;
	int status;

	if ((pid = fork()) == 0)
		exec_cmd(0, *args, fetch_path(args));
	else
	{
		waitpid(pid, &status, 0);
		//free(*args);
	}
}

static void command(char **line, t_ip *ip, char ****args)
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
			go_exec_cmd(args);
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
			go_exec_cmd(args);
	}
	else if (ip->sy != INPUT_END)
		error(MESSAGE1, ip->id_string);
}

