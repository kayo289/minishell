#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void meta_pipe(t_dlist **line, t_ip *ip)
{
	t_dlist **line2;

	while (next_ch(line, ip) == ' ')
		continue;
	line2 = NULL;
	if (ip->ch == '\0')
	{
		prompt("> ", line2);// == 0;
		/*
		{
			error2(MESSAGE2, '\0');
			exit(1);
		}
		*/
		while (((char*)(*line2)->content)[0] == '\0')
		{
			//ft_dlstclear(line);
			//free(line2);
			prompt("> ", line2);
			/*
			if (get_next_line(0, &line2) == 0)
			{
				error2(MESSAGE2, '\0');
				exit(1);
			}
			*/
		}
		ft_dlstadd_back(line, *line2);
		//*line = ft_strjoin(*line, line2);
		next_ch(line, ip);
	}
	ip->sy = PIPE;
}

static void meta_gt(t_dlist **line, t_ip *ip)
{
	if (next_ch(line, ip) == '>')
	{
		ft_charjoin(&ip->id_string, ip->ch);
		next_ch(line, ip);
		ip->sy = DGT;
	}
	else
		ip->sy = GT;
}

static void meta_lt(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	ip->sy = LT;
}

static void meta_semicolon(t_dlist **line, t_ip *ip)
{
	next_ch(line, ip);
	ip->sy = SEMICOLON;
}

void metacharacter(t_dlist **line, t_ip *ip)
{
	ft_charjoin(&ip->id_string, ip->ch);
	if (ip->ch == '|')
		meta_pipe(line, ip);
	else if (ip->ch == '>')
		meta_gt(line, ip);
	else if (ip->ch == '<')
		meta_lt(line, ip);
	else if (ip->ch == ';')
		meta_semicolon(line, ip);
}

