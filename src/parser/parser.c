#include "../../includes/minishell.h"

#define MESSAGE1 "syntax error near unexpected token " 
#define MESSAGE2 ": command not found"

static void 	next_token(t_ip **ip, t_queue *tokens)
{
	t_list *head;

	head = *tokens;
	*tokens = (*tokens)->next;
	*ip = (t_ip*)head->content;
}

static void command(t_ip **ip, t_args *args, t_queue *tokens)
{
	char **arg;

	arg = (char**)ft_calloc2(sizeof(char*), 1);
	while ((*ip)->sy == IDENTIFY || \
			(*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
	{
		if ((*ip)->sy == IDENTIFY)
		{
			arg = ft_realloc2(arg, (*ip)->id_string);
			next_token(ip, tokens);
		}
		if ((*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
		{
			next_token(ip, tokens);
			if ((*ip)->sy == IDENTIFY) 
				next_token(ip, tokens);
			else
				error(MESSAGE1, (*ip)->id_string);
		}
	}
	*args = ft_realloc3(*args, arg);
	return;
}

static void pipeline(ip, args, tokens, sv)
	t_ip **ip; t_args *args; t_queue *tokens; t_shell_var sv;
{
	command(ip, args, tokens);
	while ((*ip)->sy == PIPE)
	{
		next_token(ip, tokens);
		if ((*ip)->sy == IDENTIFY || \
			(*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
			command(ip, args, tokens);
		else
			error(MESSAGE1, (*ip)->id_string);
	}
}

static void list(t_ip **ip, t_args *args, t_queue *tokens, t_shell_var sv)
{
	while ((*ip)->sy == IDENTIFY || \
			(*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
	{
		pipeline(ip, args, tokens, sv);
		exec(args, sv);
		if ((*ip)->sy == SEMICOLON)
			next_token(ip, tokens);
	}
	else if ((*ip)->sy != INPUT_END)
		error(MESSAGE1, (*ip)->id_string);
}

void parser(t_queue *tokens, t_shell_var sv)
{
	t_ip	*head;
	t_args	args;
	
	args = ft_calloc3(sizeof(char **), 1);
	next_token(&head, tokens);
	list(&head, &args, tokens, sv);
}
