#include "../../includes/minishell.h"

static void sigint(int p_signame)
{
	write(1, "\b\b  \n", 5);
	exit(128 + p_signame);
}

static void set_signal(int p_signame)
{
	if (signal(p_signame, sigint) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

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
				if (ft_strchr("\"\'\\", ip->ch) != NULL)
					quoting(line, ip);
				else if (ft_strchr("$", ip->ch) != NULL)
					parameter(line, ip);
				else
					ip->id_string = ft_charjoin(ip->id_string, ip->ch);
				next_ch(*line, ip);
			}
			ip->sy = IDENTIFY;
		}
		else
		{
			ip->id_string = ft_charjoin(ip->id_string, ip->ch);
			metacharacter(line, ip);
		}
	}
}

void parse_line(char *line)
{
	t_ip ip;
	char ***args;

	set_signal(SIGINT);
	ip.ch = ' ';
	ip.index = 0;
	ip.id_string = ft_calloc(sizeof(char), 1);
	args = (char ***)ft_calloc3(sizeof(char **), 1);
	get_token(&line, &ip);
	input(&line, &ip, &args);
	exit(0);
}
