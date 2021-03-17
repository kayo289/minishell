#include "../../includes/minishell.h"

#define MESSAGE1 "syntax error near unexpected token " 
#define MESSAGE2 ": command not found"

void 	next_token(t_ip **ip, t_list **queue)
{
	t_list *head;

	head = *queue;
	*queue = (*queue)->next;
	*ip = (t_ip*)head->content;
}

static void command(t_ip **ip, char ****args, t_list **queue)
{
	char **arg;

	arg = (char**)ft_calloc2(sizeof(char*), 1);
	while ((*ip)->sy == IDENTIFY)
	{
		arg = ft_realloc2(arg, (*ip)->id_string);
		next_token(ip, queue);
	}
	*args = ft_realloc3(*args, arg);
	return;
}

void list(t_ip **ip, char ****args, t_list **queue, char ***shell_var)
{
	if ((*ip)->sy == IDENTIFY)
	{
		command(ip, args, queue);
		while ((*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
		{
			next_token(ip, queue);
			if ((*ip)->sy == IDENTIFY) 
				next_token(ip, queue);
			else
				error(MESSAGE1, (*ip)->id_string);
		}
		if ((*ip)->sy == PIPE)
		{
			next_token(ip, queue);
			if ((*ip)->sy == IDENTIFY)
				list(ip, args, queue, shell_var);
			else
				error(MESSAGE1, (*ip)->id_string);
		}
		if ((*ip)->sy == SEMICOLON)
		{
			go_exec_pipeline(args, shell_var);
			next_token(ip, queue);
			if ((*ip)->sy == IDENTIFY)
			{
				*args = ft_calloc3(sizeof(char **), 1);
				list(ip, args, queue, shell_var);
			}
			else if ((*ip)->sy != INPUT_END)
				error(MESSAGE1, (*ip)->id_string);
		}
		else if ((*ip)->sy == INPUT_END)
			go_exec_pipeline(args, shell_var);
	}
	else if ((*ip)->sy != INPUT_END)
		error(MESSAGE1, (*ip)->id_string);
}

