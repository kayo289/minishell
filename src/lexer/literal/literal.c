#include "../../../includes/minishell.h"

static void numeric(t_dlist **line, t_ip *ip, t_list **tokens)
{
	while (ft_isdigit(ip->ch))
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(line, ip);
	}
	if (ip->ch == '>' || ip->ch == '<')
		metacharacter(line, ip, tokens);
}

static void string(t_dlist **line, t_ip *ip)
{
	ft_charjoin(&ip->id_string, ip->ch);
	next_ch(line, ip);
}

void literal(t_dlist **line, t_ip *ip, t_list **tokens, t_shell *shell)
{
	ip->sy = IDENTIFY;
	while (ft_strchr("|><;& \0", ip->ch) == NULL)
	{
		if (ft_isdigit(ip->ch))
			numeric(line, ip, tokens);
		else if (ip->ch == '$')
			dollar(line, ip, tokens, shell);
		else if (ft_strchr("\"\'\\", ip->ch) != NULL)
			quoting(line, ip, shell);
		else
			string(line, ip);
	}
	if (ft_strchr(ip->id_string, '*') != NULL)
		wildcard(ip, tokens);
}
