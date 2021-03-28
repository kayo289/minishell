#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void double_quote(t_dlist **line, t_ip *ip)
{
	char *val;

	while (next_ch(line, ip) != '\"')
	{
		if (ip->ch == '\0')
			break;
		if (ip->ch == '$')
		{
			val = expand_parameter(line);
			ip->id_string = ft_strjoin(ip->id_string, val);
		}
		else
			ft_charjoin(&ip->id_string, ip->ch);
	}
}

static void single_quote(t_dlist **line, t_ip *ip)
{
	while (next_ch(line, ip) != '\'')
	{
		if (ip->ch == '\0')
			break;
		ft_charjoin(&ip->id_string, ip->ch);
	}
}

static void escape_character(t_dlist **line, t_ip *ip)
{
	t_dlist *line2;

	next_ch(line, ip);
	if (ip->ch == '\0')
	{
		prompt("> ", &line2);
		ft_dlstadd_back(line, line2);
	}
	else
		ft_charjoin(&ip->id_string, ip->ch);
}

void quoting(t_dlist **line, t_ip *ip)
{
	if (ip->ch == '\"')
		double_quote(line, ip);
	else if (ip->ch == '\'')
		single_quote(line, ip);
	else if (ip->ch == '\\')
		escape_character(line, ip);
}

