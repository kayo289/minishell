#include "../../includes/minishell.h"

static void dollar(line, ip, tokens)
	t_dlist **line; t_ip *ip; t_queue *tokens;
{
	char *val;
	char *str;

	if ((val = expand_parameter(line, ip, tokens)) == NULL)
	{
		if (((char *)(*line)->content)[0]== '\0')
			save_token(ip, tokens);
		next_ch(line, ip);
		return;
	}
	str = ft_strtrim(val, " \t\n");
	if (ft_strchr(" \t\n", val[0]) != NULL)
	{
		if (ft_strcmp(ip->id_string, "") != 0)
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
	ip->id_string = ft_strjoin(ip->id_string, str);
	if (ft_strchr(" \t\n", val[ft_strlen(val) - 1]) != NULL)
	{
		if (ft_strcmp(ip->id_string, "") != 0)
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
	next_ch(line, ip);
}

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

static void numeric(t_dlist **line, t_ip *ip, t_queue *tokens)
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

void literal(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	ip->sy = IDENTIFY;
	while (ft_strchr("|><; \0", ip->ch) == NULL)
	{
		if (ft_isdigit(ip->ch))
			numeric(line, ip, tokens);
		else if (ip->ch == '$')
			dollar(line, ip, tokens);
		else if (ft_strchr("\"\'\\", ip->ch) != NULL)
			quoting(line, ip, tokens);
		else
		{
			ft_charjoin(&ip->id_string, ip->ch);
			next_ch(line, ip);
		}
	}
	save_token(ip, tokens);
}
