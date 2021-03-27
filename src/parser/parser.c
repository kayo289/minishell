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

static void push(char *str, t_queue *queue)
{
	t_list *lst;
	char *s;
	
	s = ft_strdup(str);
	lst = ft_lstnew(s);
	ft_lstadd_back(queue, lst);
}

static void command(ip, args, tokens, sv)
	t_ip **ip; t_args *args; t_queue *tokens; t_shell_var *sv;
{
	char **arg;
	t_queue vars;

	arg = (char**)ft_calloc2(sizeof(char*), 1);
	vars = NULL;
	while ((*ip)->sy == IDENTIFY || \
			(*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
	{
		if ((*ip)->sy == IDENTIFY)
		{
			if (ft_strchr((*ip)->id_string, '=') != NULL)
				push((*ip)->id_string, &vars);
			else
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
	exec(args, sv, &vars);
}

static void pipeline(ip, args, tokens, sv)
	t_ip **ip; t_args *args; t_queue *tokens; t_shell_var *sv;
{
	command(ip, args, tokens, sv);
	while ((*ip)->sy == PIPE)
	{
		next_token(ip, tokens);
		if ((*ip)->sy == IDENTIFY || \
			(*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
			command(ip, args, tokens, sv);
		else
			error(MESSAGE1, (*ip)->id_string);
	}
}

static void list(ip, args, tokens, sv)
	t_ip **ip; t_args *args; t_queue *tokens; t_shell_var *sv;
{
	while ((*ip)->sy == IDENTIFY || \
			(*ip)->sy == GT || (*ip)->sy == LT || (*ip)->sy == DGT)
	{
		pipeline(ip, args, tokens, sv);
		if ((*ip)->sy == SEMICOLON)
			next_token(ip, tokens);
	}
	if ((*ip)->sy != INPUT_END)
		error(MESSAGE1, (*ip)->id_string);
}

void parser(t_queue *tokens, t_shell_var *sv)
{
	t_ip	*head;
	t_args	args;
	
	args = ft_calloc3(sizeof(char **), 1);
	next_token(&head, tokens);
	list(&head, &args, tokens, sv);
}
