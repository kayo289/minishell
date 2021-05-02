#include "../../../includes/minishell.h"

static void meta_or(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	if (ip->ch == '|')
	{
		ft_charjoin(&ip->id_string, ip->ch);
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
		ft_charjoin(&ip->id_string, ip->ch);
		ip->sy = ANDAND;
		next_ch(line, ip);
	}
	else
		ip->sy = AND;
}

static void meta_semicolon(t_dlist **line, t_ip *ip, t_list **tokens)
{
	t_ip next_ip;

	ip->sy = SEMICOLON;

	next_ch(line, &next_ip);
	while (next_ip.ch == ' ')
		next_ch(line, &next_ip);
	if (next_ip.ch == '}')
	{
		save_token(ip, tokens);
		ft_charjoin(&ip->id_string, '}');
		ip->sy = RIGHT_BRACE;
		next_ch(line, ip);
	}
	else
		ip->ch = next_ip.ch;
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
	else
		next_ch(line, ip);
}

void metacharacter(t_dlist **line, t_ip *ip, t_list **tokens)
{
	ft_charjoin(&ip->id_string, ip->ch);
	if (ip->ch == '|')
		meta_or(line, ip);
	else if (ip->ch == '&')
		meta_and(line, ip);
	else if (ip->ch == ';')
		meta_semicolon(line, ip, tokens);
	else if (ip->ch == '>' || ip->ch == '<')
		meta_redirect(line, ip);
}

