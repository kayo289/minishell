#include "../../includes/minishell.h"

static void	next_token(t_ip **ip, t_list **tokens)
{
	*ip = (t_ip*)(*tokens)->content;
	*tokens = (*tokens)->next;
}

static void simple_commands(t_ip **ip, t_list **tokens)
{
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		if ((*ip)->sy == IDENTIFY)
			next_token(ip, tokens);
		if ((*ip)->sy == REDIRECT)
		{
			next_token(ip, tokens);
			if ((*ip)->sy == IDENTIFY) 
				next_token(ip, tokens);
			else
				(*ip)->sy = ERR;
		}
	}
}

static void pipelines(t_ip **ip, t_list **tokens)
{
	simple_commands(ip, tokens);
	while ((*ip)->sy == PIPE)
	{
		next_token(ip, tokens);
		if ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
			simple_commands(ip, tokens);
		else
			(*ip)->sy = ERR;
	}
}

static void lists(t_ip **ip, t_list **tokens)
{
	/*
	while ((*ip)->sy == IDENTIFY)
	{
		if (ft_strchr((*ip)->id_string, '=') != NULL)
			next_token(ip, tokens);
		else
			break;
	}
	*/
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		pipelines(ip, tokens);
		if ((*ip)->sy == SEMICOLON)
			next_token(ip, tokens);
	}
}

/*
static void compound_commands(t_ip **ip, t_list **tokens, t_shell *shell)
{
	//t_dlist *line2;
	//t_list	*tokens2;

	next_token(ip, tokens);
	lists(ip, tokens, shell);
	if ((*ip)->sy == RIGHT_BRACE)
		next_token(ip, tokens);
	else
	{
		while ((*ip)->sy != RIGHT_BRACE)
		{
			prompt("> ", &line2, shell);
			lexer(&line2, &tokens2, shell);
			ft_lstadd_back(tokens, tokens2);

			compound_commands(ip, tokens, shell);
		}
		next_token(ip, tokens);
	}
}
*/

void parser(t_list *tokens, t_shell *shell)
{
	t_ip	*ip;
	
	next_token(&ip, &tokens);
	if (ip->sy == LEFT_BRACE)
	{
		next_token(&ip, &tokens);
		lists(&ip, &tokens);
		if (ip->sy == RIGHT_BRACE)
			next_token(&ip, &tokens);
	//	compound_commands(&ip, &tokens, shell);
	}
	else
		lists(&ip, &tokens);

	if (ip->sy == INPUT_END)
		interpreter(tokens, shell);
	else if (ip->sy == ERR)
		err_syntax(&ip, shell);
}
