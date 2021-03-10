#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void meta_pipe(char **line, t_ip *ip)
{
	char *line2;

	while (next_ch(*line, ip) == ' ')
		continue;
	if (ip->ch == '\0')
	{
		write(1, "> ", 2);
		if (get_next_line(0, &line2) == 0)
		{
			error2(MESSAGE2, '\0');
			exit(1);
		}
		while (*line2 == '\0')
		{
			write(1, "> ", 2);
			free(line2);
			if (get_next_line(0, &line2) == 0)
			{
				error2(MESSAGE2, '\0');
				exit(1);
			}
		}
		*line = ft_strjoin(*line, line2);
		next_ch(*line, ip);
	}
	ip->sy = PIPE;
}

static void meta_gt(char **line, t_ip *ip)
{
	if (next_ch(*line, ip) == '>')
	{
		ip->id_string = ft_charjoin(ip->id_string, ip->ch);
		next_ch(*line, ip);
		ip->sy = DGT;
	}
	else
		ip->sy = GT;
}

static void meta_lt(char **line, t_ip *ip)
{
	next_ch(*line, ip);
	ip->sy = LT;
}

static void meta_semicolon(char **line, t_ip *ip)
{
	next_ch(*line, ip);
	ip->sy = SEMICOLON;
}

void metacharacter(char **line, t_ip *ip)
{
	if (ip->ch == '|')
		meta_pipe(line, ip);
	else if (ip->ch == '>')
		meta_gt(line, ip);
	else if (ip->ch == '<')
		meta_lt(line, ip);
	else if (ip->ch == ';')
		meta_semicolon(line, ip);
}

