#include "../../../includes/minishell.h"

static void escape_character(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	ft_charjoin(&ip->id_string, ip->ch);
}

static void double_quote(t_dlist **line, t_ip *ip)
{
	while (next_ch(line, ip) != '\"')
	{
		if (ip->ch == '\0')
			break;
		else
			ft_charjoin(&ip->id_string, ip->ch);
	}
	ft_charjoin(&ip->id_string, ip->ch);
}

static void single_quote(t_dlist **line, t_ip *ip)
{
	while (next_ch(line, ip) != '\'')
	{
		if (ip->ch == '\0')
			break;
		else
			ft_charjoin(&ip->id_string, ip->ch);
	}
	ft_charjoin(&ip->id_string, ip->ch);
}

void quoting(t_dlist **line, t_ip *ip)
{
	ft_charjoin(&ip->id_string, ip->ch);
	if (ip->ch == '\"')
		double_quote(line, ip);
	else if (ip->ch == '\'')
		single_quote(line, ip);
	else if (ip->ch == '\\')
		escape_character(line, ip);
	next_ch(line, ip);
}
