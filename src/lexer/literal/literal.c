#include "../../../includes/minishell.h"

static void dollar(t_dlist **line, t_ip *ip)
{
	ip_charjoin(ip, ip->ch);
	next_ch(line, ip);
	if (ip->ch == '{')
	{
		ip_charjoin(ip, ip->ch);
		while (next_ch(line, ip) != '}')
		{
			if (ip->ch == '\0')
				break;
			ip_charjoin(ip, ip->ch);
		}
		ip_charjoin(ip, ip->ch);
		next_ch(line, ip);
	}
	else
	{
		while (ft_issnack_case(ip->ch)) 
		{
			ip_charjoin(ip, ip->ch);
			next_ch(line, ip);
		}
	}
}

static void numeric(t_dlist **line, t_ip *ip)
{
	while (ft_isdigit(ip->ch))
	{
		ip_charjoin(ip, ip->ch);
		next_ch(line, ip);
	}
	if (ip->ch == '>' || ip->ch == '<')
		metacharacter(line, ip);
}

static void string(t_dlist **line, t_ip *ip)
{
	ip_charjoin(ip, ip->ch);
	next_ch(line, ip);
}

void literal(t_dlist **line, t_ip *ip, t_list **tokens)
{
	ip->sy = IDENTIFY;
	while (ft_strchr("|><& \t\0", ip->ch) == NULL)
	{
		if (ft_isdigit(ip->ch))
			numeric(line, ip);
		else if (ip->ch == '$')
			dollar(line, ip);
		else if (ft_strchr("\"\'", ip->ch) != NULL)
			quoting(line, ip);
		else
			string(line, ip);
	}
	if (ft_strchr(ip->id_string, '*') != NULL)
		wildcard(ip, tokens);
}
