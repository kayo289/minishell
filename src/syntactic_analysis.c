#include "../includes/minishell.h"

void error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

void input(char **line, t_ip *ip)
{
	if (ip->sy == IDENTIFY)
	{
		command(line, ip);
		if (ip->sy == GT || ip->sy == LT || ip->sy == DGT)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY) 
				get_token(line, ip);
			else
				error(ft_strjoin("syntax error near unexpected token ", 
														ip->id_string));
		}
		if (ip->sy == PIPE)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY)
				input(line, ip);
			else
				error(ft_strjoin("syntax error near unexpected token ", 
														ip->id_string));
		}
		if (ip->sy == SEMICOLON)
		{
			get_token(line, ip);
			if (ip->sy == IDENTIFY)
				input(line, ip);
			else
				error(ft_strjoin("syntax error near unexpected token ", 
														ip->id_string));
		}
	}
	else
		error(ft_strjoin("syntax error near unexpected token ", 
													ip->id_string));
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
		error(ft_strjoin(*line, ": command not found"));
	else
	{
		while (ip->sy == IDENTIFY)
			get_token(line, ip);
	}
}
