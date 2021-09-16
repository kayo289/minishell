#include "../../../includes/minishell.h"

static void meta_or(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	if (ip->ch == '|')
	{
		ip_charjoin(ip, ip->ch);
		ip->sy = OROR;
		next_ch(line, ip);
	}
	else
		ip->sy = PIPE;
}

static void meta_and(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	if (ip->ch == '&')
	{
		ip_charjoin(ip, ip->ch);
		ip->sy = ANDAND;
		next_ch(line, ip);
	}
	else
		ip->sy = AND;
}

static void meta_redirect(t_dlist **line, t_ip *ip)
{
	ip->sy = REDIRECT;
	if (ip->ch == '>')
	{
		next_ch(line, ip);
		if (ip->ch == '>')
		{
			ft_charjoin(&ip->id_string, ip->ch);
			next_ch(line, ip);
		}
	}
	else if (ip->ch == '<')
	{
		next_ch(line, ip);
		if (ip->ch == '<')
		{
			ft_charjoin(&ip->id_string, ip->ch);
			next_ch(line, ip);
		}
	}
	else
		next_ch(line, ip);
}

void metacharacter(t_dlist **line, t_ip *ip)
{
	ip_charjoin(ip, ip->ch);
	if (ip->ch == '|')
		meta_or(line, ip);
	else if (ip->ch == '&')
		meta_and(line, ip);
	else if (ip->ch == '>' || ip->ch == '<')
		meta_redirect(line, ip);
}

