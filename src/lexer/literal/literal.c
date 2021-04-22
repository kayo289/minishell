#include "../../../includes/minishell.h"

static void dollar(t_dlist **line, t_ip *ip, t_list **tokens, t_shell *shell)
{
	char *val;
	char *str;

	val = expand_parameter(line, ip, shell);
	if (val == NULL)
	{
		next_ch(line, ip);
		get_token(line, ip, tokens, shell);
		return;
	}
	str = ft_strtrim(val, " \t\n");
	if (ft_strchr(" \t\n", val[0]) != NULL)
	{
		if (*ip->id_string != '\0')
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
	ip->id_string = ft_strjoin(ip->id_string, str);
	if (ft_strchr(" \t\n", val[ft_strlen(val) - 1]) != NULL)
	{
		if (*ip->id_string != '\0')
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
	next_ch(line, ip);
}

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
	while (ft_strchr("|><; \0", ip->ch) == NULL)
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
}
