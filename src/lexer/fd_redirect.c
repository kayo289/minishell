#include "../../includes/minishell.h"

static void meta_redirect(t_dlist **line, t_ip *ip)
{
	if (next_ch(line, ip) == '>')
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(line, ip);
	}
	ip->sy = REDIRECT;
}

void fd_redirect(t_dlist **line, t_ip *ip)
{
	while (ft_isdigit(ip->ch))
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(line, ip);
	}
	if (ip->ch == '>')
		meta_redirect(line, ip);
	return;
}
