#include "../../includes/minishell.h"

char next_ch(t_dlist **line, t_ip *ip)
{
	ip->ch = ((char*)(*line)->content)[0];
	if ((*line)->next != NULL)
		*line = (*line)->next;
	//ft_dlstdelone();
	return (ip->ch);
}

void save_token(t_ip *ip, t_queue *tokens)
{
	t_list	*lst;
	t_ip	*tmp;

	tmp = malloc(sizeof(t_ip));
	*tmp = *ip;
	lst = ft_lstnew(tmp);
	ft_lstadd_back(tokens, lst);
	ip->id_string = ft_calloc(sizeof(char), 1);
}

static void get_token(line, ip, tokens, shell)
	t_dlist **line; t_ip *ip; t_queue *tokens; t_shell *shell;
{
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(line, ip);
	if (ip->ch == '\0')
	{
		ip->sy = INPUT_END;
		return;
	}
	ip->sy = IDENTIFY;
	if (ft_isdigit(ip->ch))
		number(line, ip, tokens);
	if (ft_strchr("|><;", ip->ch) == NULL)
		while (ft_strchr("|><; \0", ip->ch) == NULL)
		{
			if (ft_strchr("$", ip->ch) != NULL)
				dollar(line, ip, tokens);
			else if (ft_strchr("\"\'\\", ip->ch) != NULL)
				quoting(line, ip);
			else
				ft_charjoin(&ip->id_string, ip->ch);
			next_ch(line, ip);
		}
	else
		metacharacter(line, ip);
	save_token(ip, tokens);
	get_token(line, ip, tokens, shell);
}

void lexer(t_dlist **line, t_queue *tokens, t_shell *shell)
{
	t_ip	ip;

	ip.ch = ' ';
	ip.id_string = ft_calloc(sizeof(char), 1);
	*tokens = NULL;
	get_token(line, &ip, tokens, shell);
	save_token(&ip, tokens);
}
