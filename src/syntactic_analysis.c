#include "../includes/minishell.h"

void error(char *message, char *token)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(token, 2);
	exit(1);
}

void input(char **line, t_ip *ip)
{
	if (ip->sy == IDENTIFY)
	{
		command(line, ip);
		while (ip->sy == GT || ip->sy == LT || ip->sy == DGT)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY) 
				get_token(line, ip);
			else
				error("syntax error near unexpected token ", ip->id_string);
		}
		if (ip->sy == PIPE)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY)
				input(line, ip);
			else
				error("syntax error near unexpected token ", ip->id_string);
		}
		if (ip->sy == SEMICOLON)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY)
				input(line, ip);
			else if (ip->sy != INPUT_END)
				error("syntax error near unexpected token ", ip->id_string);
		}
	}
	else if (ip->sy != INPUT_END)
		error("syntax error near unexpected token ", ip->id_string);
}

void command(char **line, t_ip *ip)
{
	int i;
	const char *cmds[] =
		{"cd", "echo", "pwd", "env", "export", "unset", "exit", NULL};

	i = 0;
	while (cmds[i] != NULL)
	{
		if (equal((char*)cmds[i], ip->id_string))
			break;
		i++;
	}
	if (cmds[i] == NULL)
		error(*line, ": command not found");
	else
	{
		while (ip->sy == IDENTIFY)
			get_token(line, ip);
	}
}
