#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void line_continuation(char **line, t_ip *ip, char find_ch)
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

void escape_char(char **line, t_ip *ip)
{
	char *line2;

	next_ch(*line, ip);
	if (ip->ch == '\0')
	{
		write(1, "> ", 2);
		get_next_line(0, &line2);
		*line = ft_strjoin(*line, line2);
	}
	else
		ft_charjoin(&ip->id_string, ip->ch);
}

void quoting(char **line, t_ip *ip)
{
	if (ip->ch == '\"')
		line_continuation(line, ip, '\"');
	else if (ip->ch == '\'')
		line_continuation(line, ip, '\'');
	else if (ip->ch == '\\')
		escape_char(line, ip);
}
