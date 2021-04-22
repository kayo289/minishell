#include "../../includes/minishell.h"

static void	next_token(t_ip **ip, t_list **tokens)
{
	if ((*ip)->sy == ERR)
		return;
	*ip = (t_ip*)(*tokens)->content;
	*tokens = (*tokens)->next;
}

static void simple_command(t_ip **ip, t_list **tokens, t_data *data)
{
	char	**args;

	while ((*ip)->sy == IDENTIFY)
	{
		if (ft_strchr((*ip)->id_string, '=') != NULL)
			enq(&data->vars, (*ip)->id_string);
		else
			break;
		next_token(ip, tokens);
	}

	args = (char **)ft_calloc2(sizeof(char*), 1);
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		if ((*ip)->sy == IDENTIFY)
			args = ft_realloc2(args, (*ip)->id_string);
		else if ((*ip)->sy == REDIRECT)
		{
			enq(&data->fds, (*ip)->id_string);
			next_token(ip, tokens);
			if ((*ip)->sy == IDENTIFY)
				enq(&data->fds, (*ip)->id_string);
			else
				(*ip)->sy = ERR;
		}
		next_token(ip, tokens);
	}
	ft_lstadd_back(&data->args, ft_lstnew(args));
}

static void pipeline(t_ip **ip, t_list **tokens, t_list **datas)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->fds = NULL;
	data->vars = NULL;
	simple_command(ip, tokens, data);
	if ((*ip)->sy == PIPE)
	{
		data->grammer = PIPELINE;
		while ((*ip)->sy == PIPE)
		{
			next_token(ip, tokens);
			if ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
				simple_command(ip, tokens, data);
			else
				(*ip)->sy = ERR;
		}
	}
	else
		data->grammer = SIMPLECMD;
	ft_lstadd_back(datas, ft_lstnew(data));
}

static void lists(t_ip **ip, t_list **tokens, t_list **datas)
{
	while ((*ip)->sy == IDENTIFY || (*ip)->sy == REDIRECT)
	{
		pipeline(ip, tokens, datas);
		if ((*ip)->sy == SEMICOLON)
			next_token(ip, tokens);
	}
}

void parser(t_list *tokens, t_shell *shell)
{
	t_ip	*ip;
	t_list *datas;
	
	datas = NULL;
	next_token(&ip, &tokens);
	if (ip->sy == LEFT_BRACE)
	{
		next_token(&ip, &tokens);
		lists(&ip, &tokens, &datas);
		if (ip->sy == RIGHT_BRACE)
			next_token(&ip, &tokens);
	}
	else
		lists(&ip, &tokens, &datas);

	if (ip->sy == INPUT_END)
		interpreter(datas, shell);
	else
		err_syntax(&ip, shell);
}

/* To multiple line
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
