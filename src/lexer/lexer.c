#include "../../includes/minishell.h"

char next_ch(char *line, t_ip *ip)
{
	ip->ch = line[ip->index];
	if (line[ip->index] != '\0')
		ip->index++;
	return (ip->ch);
}

void get_token(char **line, t_ip *ip)
{
	//free(ip->id_string);
	ip->id_string = ft_calloc(sizeof(char), 1);
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(*line, ip);
	if (ip->ch == '\0')
		ip->sy = INPUT_END;
	else
	{
		if (ft_strchr("|><;", ip->ch) == NULL)
		{
			while (ft_strchr("|><; \0", ip->ch) == NULL)
			{
				if (ft_strchr("$", ip->ch) != NULL)
					parameter_expansion(line, ip);
				else if (ft_strchr("\"\'\\", ip->ch) != NULL)
					quoting(line, ip);
				else
					ft_charjoin(&ip->id_string, ip->ch);
				next_ch(*line, ip);
			}
			ip->sy = IDENTIFY;
		}
		else
			metacharacter(line, ip);
	}
}

void parse_line(char *line)
{
	t_ip ip;
	char ***args;

	ip.ch = ' ';
	ip.index = 0;
	ip.id_string = ft_calloc(sizeof(char), 1);
	args = (char ***)ft_calloc3(sizeof(char **), 1);
	set_signal(SIGINT);
	get_token(&line, &ip);
	input(&line, &ip, &args);
}
