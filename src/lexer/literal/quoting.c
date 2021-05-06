#include "../../../includes/minishell.h"

static void escape_character(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	ft_charjoin(&ip->id_string, ip->ch);
}

static void double_quote(t_dlist **line, t_ip *ip, t_shell *shell)
{
	t_ip next_ip;
	char *val;

	while (next_ch(line, ip) != '\"')
	{
		if (ip->ch == '\0')
			break;
		if (ip->ch == '$')
		{
			val = expand_parameter(line, ip, shell);
			if (val == NULL)
				val = " ";
			ip->id_string = ft_strjoin(ip->id_string, val);
			if(ip->ch == '\"')
			{
				next_ch(line, ip);
				return;
			}
		}
		if (ip->ch == '\\')
		{
			next_ch(line, &next_ip);
			if (ft_strchr("$`\\\"", next_ip.ch) != NULL)
				ft_charjoin(&ip->id_string, next_ip.ch);
			else
			{
				ft_charjoin(&ip->id_string, ip->ch);
				ft_charjoin(&ip->id_string, next_ip.ch);
			}
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

void quoting(t_dlist **line, t_ip *ip, t_shell *shell)
{
	if (ip->ch == '\"')
		double_quote(line, ip, shell);
	else if (ip->ch == '\'')
		single_quote(line, ip);
	else if (ip->ch == '\\')
		escape_character(line, ip);
	next_ch(line, ip);
}

