#include "../../../includes/minishell.h"

static void escape_character(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	ft_charjoin(&ip->id_string, ip->ch);
}

static void double_quote(t_dlist **line, t_ip *ip, t_queue *tokens, t_shell *shell)
{
	char *val;

	while (next_ch(line, ip) != '\"')
	{
		if (ip->ch == '\0')
			break;
		else if (ip->ch == '$')
		{
			val = expand_parameter(line, ip, tokens, shell);
			ip->id_string = ft_strjoin(ip->id_string, val);
		}
		else if (ip->ch == '\\')
			escape_character(line, ip);
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
		else if (ip->ch == '\\')
			escape_character(line, ip);
		else
			ft_charjoin(&ip->id_string, ip->ch);
	}
}

void quoting(t_dlist **line, t_ip *ip, t_queue *tokens, t_shell *shell)
{
	if (ip->ch == '\"')
		double_quote(line, ip, tokens, shell);
	else if (ip->ch == '\'')
		single_quote(line, ip);
	else if (ip->ch == '\\')
		escape_character(line, ip);
	ip->sy = IDENTIFY; 
	next_ch(line, ip);
}

