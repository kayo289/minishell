#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void input_waiting(char **line, t_ip *ip, char find_ch)
{
	char *line2;

	while (next_ch(*line, ip) != find_ch)
	{
		if (ip->ch == '\0')
		{
			write(1, "> ", 2);
			if (get_next_line(0, &line2) == 0)
			{
				error2(MESSAGE1, find_ch);
				error2(MESSAGE2, '\0');
				exit(1);
			}
			*line = ft_strjoin(*line, "\n");
			*line = ft_strjoin(*line, line2);
		}
		else
			ft_charjoin(&ip->id_string, ip->ch);
	}
}

void parameter(char **line, t_ip *ip)
{
	if (ip->ch == '$')
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(*line, ip);
		if (ip->ch == '{' || ip->ch == '(')
		{
			ft_charjoin(&ip->id_string, ip->ch);
			if (ip->ch == '{')
				input_waiting(line, ip, '}');
			else if (ip->ch == '(')
				input_waiting(line, ip, ')');
			ft_charjoin(&ip->id_string, ip->ch);
		}
	}
}

