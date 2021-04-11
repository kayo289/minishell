#include "../../../includes/minishell.h"

static void meta_pipe(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	ip->sy = PIPE;
	next_ch(line, ip);
	save_token(ip, tokens);
}

static void meta_redirect(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	if (next_ch(line, ip) == '>')
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(line, ip);
	}
	ip->sy = REDIRECT;
	save_token(ip, tokens);
}

static void meta_semicolon(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	t_ip next_ip;

	ip->sy = SEMICOLON;
	save_token(ip, tokens);

	next_ch(line, &next_ip);
	while (next_ip.ch == ' ')
		next_ch(line, &next_ip);
	if (next_ip.ch == '}')
	{
		ft_charjoin(&ip->id_string, '}');
		ip->sy = RIGHT_BRACE;
		save_token(ip, tokens);
		next_ch(line, ip);
	}
	else
		ip->ch = next_ip.ch;
}

void metacharacter(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	ft_charjoin(&ip->id_string, ip->ch);
	if (ip->ch == '|')
		meta_pipe(line, ip, tokens);
	else if (ip->ch == '>' || ip->ch == '<')
		meta_redirect(line, ip, tokens);
	else if (ip->ch == ';')
		meta_semicolon(line, ip, tokens);
}

