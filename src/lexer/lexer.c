#include "../../includes/minishell.h"

void ip_charjoin(t_ip *ip, char ch)
{
	char *s;
	char *tmp;

	s = ft_calloc(sizeof(char), 2);
	s[0] = ch; 
	tmp = ip->id_string;
	ip->id_string = ft_strjoin(ip->id_string, s);
	ft_lstadd_back(&ip->id_lst, ft_lstnew(s));
	free(tmp);
}

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
	ip->id_lst = NULL;
}

void get_token(t_dlist **line, t_ip *ip, t_list **tokens)
{
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(line, ip);
	if (ip->ch == '\0')
	{
		ip->sy = INPUT_END;
		return;
	}
	else if (ft_strchr("|&><", ip->ch) == NULL)
		literal(line, ip, tokens);
	else
		metacharacter(line, ip);
}

void lexer(t_dlist *line, t_list **tokens)
{
	t_ip ip;

	*tokens = NULL;
	ip.id_string = ft_calloc(sizeof(char), 1);
	ip.id_lst = NULL;
	next_ch(&line, &ip);

	while (ip.ch != '\0')
	{
		get_token(&line, &ip, tokens);
		save_token(&ip, tokens);
	}
	get_token(&line, &ip, tokens);
	save_token(&ip, tokens);
	free(ip.id_string);
}
