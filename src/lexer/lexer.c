#include "../../includes/minishell.h"

char next_ch(t_dlist **line, t_ip *ip)
{
	if (*line != NULL)
	{
		ip->ch = ((char*)(*line)->content)[0];
		*line = (*line)->next;
	}
	else
		ip->ch = '\0';
	return (ip->ch);
}

void save_token(t_ip *ip, t_list **tokens)
{
	t_ip	*tmp;

	tmp = malloc(sizeof(t_ip));
	*tmp = *ip;
	ft_lstadd_back(tokens, ft_lstnew(tmp));
	ip->id_string = ft_calloc(sizeof(char), 1);
}

void get_token(t_dlist **line, t_ip *ip, t_list **tokens, t_shell *shell)
{
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(line, ip);
	if (ip->ch == '\0')
	{
		ip->sy = INPUT_END;
		return;
	}
	else if (ft_strchr("|&><;", ip->ch) == NULL)
		literal(line, ip, tokens, shell);
	else
		metacharacter(line, ip, tokens);
}

static void brace(t_dlist **line, t_ip *ip, t_list **tokens)
{
	if (ip->ch == '{')
	{
		ft_charjoin(&ip->id_string, '{');
		next_ch(line, ip);
		if (ip->ch == ' ')
		{
			ip->sy = LEFT_BRACE; 
			save_token(ip, tokens);
			next_ch(line, ip);
		}
	}
	else if (ip->ch == '}')
	{
		ft_charjoin(&ip->id_string, '}');
		ip->sy = RIGHT_BRACE; 
		save_token(ip, tokens);
		next_ch(line, ip);
	}
}

void lexer(t_dlist *line, t_list **tokens, t_shell *shell)
{
	t_ip ip;

	*tokens = NULL;
	ip.id_string = ft_calloc(sizeof(char), 1);
	next_ch(&line, &ip);

	brace(&line, &ip, tokens);
	while (ip.ch != '\0')
	{
		get_token(&line, &ip, tokens, shell);
		save_token(&ip, tokens);
	}
	get_token(&line, &ip, tokens, shell);
	save_token(&ip, tokens);
	free(ip.id_string);
}
