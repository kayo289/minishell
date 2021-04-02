#include "../../includes/minishell.h"

char next_ch(t_dlist **line, t_ip *ip)
{
	t_dlist *tmp;

	ip->ch = ((char*)(*line)->content)[0];
	if ((*line)->next != NULL)
	{
		tmp = *line;
		*line = (*line)->next;
		ft_dlstdelone(tmp, free);
	}
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

void get_token(line, ip, tokens)
	t_dlist **line; t_ip *ip; t_queue *tokens;
{
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(line, ip);
	if (ip->ch == '\0')
	{
		ip->sy = INPUT_END;
		save_token(ip, tokens);
		return;
	}
	if (ft_strchr("|><;", ip->ch) == NULL)
		literal(line, ip, tokens);
	else
		metacharacter(line, ip, tokens);
	get_token(line, ip, tokens);
}

void lexer(t_dlist **line, t_queue *tokens)
{
	t_ip	ip;

	*tokens = NULL;
	ip.id_string = ft_calloc(sizeof(char), 1);
	if (next_ch(line, &ip) == '{')
	{
		ft_charjoin(&ip.id_string, ip.ch);
		if (next_ch(line, &ip) == ' ')
		{
			ip.sy = LEFT_BRACE; 
			save_token(&ip, tokens);
		}
	}
	get_token(line, &ip, tokens);
}
