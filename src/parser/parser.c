#include "../../includes/minishell.h"

static void simple_commands(ip, tokens, args, fds)
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

static void pipelines(ip, tokens, shell)
	t_ip **ip; t_queue *tokens; t_shell *shell;
{
	char	**args;
	t_queue	fds;
	int		**ppfd;
	int		pfd[2];

	pipe(pfd);
	ppfd = malloc(sizeof(int*));
	*ppfd = pfd;
	simple_commands(ip, tokens, &args, &fds);
	while ((*ip)->sy == PIPE)
	{
		next_token(ip, tokens);
		if ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
		{
			exec_a(&args, &fds, ppfd, shell);
			simple_commands(ip, tokens, &args, &fds);
		}
		else
			err_syntax(ip);
	}
	exec_b(&args, &fds, ppfd, shell);
}

static void lists(ip, tokens, shell)
	t_ip **ip; t_queue *tokens; t_shell *shell;
{
	assign_variable(ip, tokens, shell);
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		pipelines(ip, tokens, shell);
		if ((*ip)->sy == SEMICOLON)
			next_token(ip, tokens);
	}
}

static void compound_commands(ip, tokens, shell)
	t_ip **ip; t_queue *tokens; t_shell *shell;
{
	next_token(ip, tokens);
	lists(ip, tokens, shell);
	if ((*ip)->sy == RIGHT_BRACE)
		next_token(ip, tokens);
}

void parser(t_queue *tokens, t_shell *shell)
{
	t_ip	*ip;
	
	next_token(&ip, tokens);
	if (ip->sy == LEFT_BRACE)
		compound_commands(&ip, tokens, shell);
	else
		lists(&ip, tokens, shell);
	if (ip->sy != INPUT_END)
		err_syntax(&ip);
}
