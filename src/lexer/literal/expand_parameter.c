#include "../../../includes/minishell.h"

#include "../../../includes/minishell.h"

static void brace(t_dlist **line, char **key, t_ip *ip, t_shell *shell)
{
	t_dlist *line2;

	next_ch(line, ip);
	while (next_ch(line, ip) != '}')
	{
		if (ip->ch == '\0')
		{
			prompt("> ", &line2, shell);
			ft_dlstadd_back(line, ft_dlstnew("\n"));
			ft_dlstadd_back(line, line2);
		}
		else
			ft_charjoin(key, ip->ch);
	}
	next_ch(line, ip);
}

char *expand_parameter(t_dlist **line, t_ip *ip, t_shell *shell)
{
	char *key;
	char *val;

	key = ft_calloc(sizeof(char), 1);
	next_ch(line, ip);
	if (!ft_issnack_case(ip->ch))
		return ("$");
	if (ip->ch == '?')
	{
		next_ch(line, ip);
		return (ft_itoa(shell->exit_status));
	}
	if (ip->ch == '{')
		brace(line, &key, ip, shell);
	else
	{
		while (ft_issnack_case(ip->ch))
		{
			ft_charjoin(&key, ip->ch);
			next_ch(line, ip);
		}
	}
	val = getenv(key);
	free(key);
	return (val);
}
