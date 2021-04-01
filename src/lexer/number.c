#include "../../includes/minishell.h"

static void meta_redirect(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	ft_charjoin(&ip->id_string, ip->ch);
	if (next_ch(line, ip) == '>')
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(line, ip);
	}
	ip->sy = REDIRECT;
	save_token(ip, tokens);
}

void number(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	while (ft_isdigit(ip->ch))
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(line, ip);
	}
	if (ip->ch == '>')
		meta_redirect(line, ip, tokens);
	return;
}
