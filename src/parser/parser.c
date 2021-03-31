#include "../../includes/minishell.h"

static void 	next_token(t_ip **ip, t_queue *tokens)
{
	t_list *head;

	head = *tokens;
	*tokens = (*tokens)->next;
	*ip = (t_ip*)head->content;
}

static void command(ip, tokens, args, fds)
		t_ip **ip; t_queue *tokens, *fds; t_args args;
{
	*args = (char **)ft_calloc2(sizeof(char*), 1);
	*fds = NULL;
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		if ((*ip)->sy == IDENTIFY)
		{
			*args = ft_realloc2(*args, (*ip)->id_string);
			next_token(ip, tokens);
		}
		if ((*ip)->sy == REDIRECT)
		{
			push(((*ip)->id_string), fds);
			next_token(ip, tokens);
			if ((*ip)->sy == IDENTIFY) 
			{
				push(((*ip)->id_string), fds);
				next_token(ip, tokens);
			}
			else
				err_syntax(ip);
		}
	}
}

static void pipeline(ip, tokens, sv)
	t_ip **ip; t_queue *tokens; t_shell_var *sv;
{
	char	**args;
	t_queue	fds;
	int		**ppfd;
	int		pfd[2];

	pipe(pfd);
	ppfd = malloc(sizeof(int*));
	*ppfd = pfd;
	command(ip, tokens, &args, &fds);
	while ((*ip)->sy == PIPE)
	{
		next_token(ip, tokens);
		if ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
		{
			exec_a(&args, &fds, ppfd, sv);
			command(ip, tokens, &args, &fds);
		}
		else
			err_syntax(ip);
	}
	exec_b(&args, &fds, ppfd, sv);
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
			{
				while (vars != NULL)
					set_shell_var(*sv, pop(&vars));
			}
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
		err_syntax(ip);
}

void parser(t_queue *tokens, t_shell_var *sv)
{
	t_ip	*ip;
	
	next_token(&ip, tokens);
	list(&ip, tokens, sv);
}
