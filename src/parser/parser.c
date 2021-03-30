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

static void command(ip, tokens, sv)
		t_ip **ip; t_queue *tokens; t_shell_var *sv;
{
	char **args;
	t_queue fds;

	args = (char **)ft_calloc2(sizeof(char*), 1);
	fds = NULL;
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		if ((*ip)->sy == IDENTIFY)
		{
			args = ft_realloc2(args, (*ip)->id_string);
			next_token(ip, tokens);
		}
		if ((*ip)->sy == REDIRECT)
		{
			push(((*ip)->id_string), &fds);
			next_token(ip, tokens);
			if ((*ip)->sy == IDENTIFY) 
			{
				push(((*ip)->id_string), &fds);
				next_token(ip, tokens);
			}
			else
			{
				error(MESSAGE1, (*ip)->id_string);
				(*ip)->sy = INPUT_END;
			}
		}
	}
	exec(&args, &fds, sv);
}

static void pipeline(ip, tokens, sv)
	t_ip **ip; t_queue *tokens; t_shell_var *sv;
{
	command(ip, tokens, sv);
	while ((*ip)->sy == PIPE)
	{
		next_token(ip, tokens);
		if ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
			command(ip, tokens, sv);
		else
		{
			error(MESSAGE1, (*ip)->id_string);
			(*ip)->sy = INPUT_END;
		}
	}
}

static void list(ip, tokens, sv)
	t_ip **ip; t_queue *tokens; t_shell_var *sv;
{
	t_queue vars;

	vars = NULL;
	while ((*ip)->sy == IDENTIFY)
	{
		if (ft_strchr((*ip)->id_string, '=') != NULL)
		{
			push((*ip)->id_string, &vars);
			next_token(ip, tokens);
			if ((*ip)->sy == INPUT_END)
				assign_variable(&vars, sv);
		}
		else
			break;
	}
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		pipeline(ip, tokens, sv);
		if ((*ip)->sy == SEMICOLON)
			next_token(ip, tokens);
	}
	if ((*ip)->sy != INPUT_END)
		error(MESSAGE1, (*ip)->id_string);
}

void parser(t_queue *tokens, t_shell_var *sv)
{
	t_ip	*ip;
	
	next_token(&ip, tokens);
	list(&ip, tokens, sv);
}
