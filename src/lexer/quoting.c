#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void double_quote(char **line, t_ip *ip)
{
	char *line2;
	char *val;

	while (next_ch(*line, ip) != '\"')
	{
		if (ip->ch == '\0')
		{
			write(1, "> ", 2);
			if (get_next_line(0, &line2) == 0)
			{
				error2(MESSAGE1, '\"');
				error2(MESSAGE2, '\0');
				exit(1);
			}
			*line = ft_strjoin(*line, "\n");
			*line = ft_strjoin(*line, line2);
		}
		else if (ip->ch == '$')
		{
			val = expand_parameter(line, ip);
			ip->id_string = ft_strjoin(ip->id_string, val);
		}
		else
			ft_charjoin(&ip->id_string, ip->ch);
	}
}

static void single_quote(char **line, t_ip *ip)
{
	char *line2;

	while (next_ch(*line, ip) != '\'')
	{
		if (ip->ch == '\0')
		{
			write(1, "> ", 2);
			if (get_next_line(0, &line2) == 0)
			{
				error2(MESSAGE1, '\'');
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

static void escape_character(char **line, t_ip *ip)
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
		double_quote(line, ip);
	else if (ip->ch == '\'')
		single_quote(line, ip);
	else if (ip->ch == '\\')
		escape_character(line, ip);
}

