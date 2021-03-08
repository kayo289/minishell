#include "../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

void error2(char *message, char token)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd(token, 2);
	ft_putchar_fd('\n', 2);
}

bool equal(char *s, char *t)
{
	if (ft_strlen(s) != ft_strlen(t))
		return (false);
	else if (ft_strncmp(s, t, ft_strlen(s)) == 0)
		return (true);
	return (false);
}

char *ft_charjoin(char *old, char c)
{
	char *new;
	int len;
	int i;

	len = ft_strlen(old);
	new = (char *)malloc(sizeof(char) * (len + 2));
	i = -1;
	while (++i < len)
		new[i] = old[i];
	new[i++] = c;
	new[i] = '\0';
	free(old);
	return (new);
}

char next_ch(char *line, t_ip *ip)
{
	ip->ch = line[ip->index];
	if (line[ip->index] != '\0')
		ip->index++;
	return (ip->ch);
}

void check_token2_sub(char **line, t_ip *ip, char find_ch)
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
			ip->id_string = ft_charjoin(ip->id_string, ip->ch);
	}
}

void check_token2(char **line, t_ip *ip)
{
	if (ip->ch == '\"')
		check_token2_sub(line, ip, '\"');
	else if (ip->ch == '\'')
		check_token2_sub(line, ip, '\'');
	else if (ip->ch == '$')
	{
		ip->id_string = ft_charjoin(ip->id_string, ip->ch);
		next_ch(*line, ip);
		if (ip->ch == '{' || ip->ch == '(')
		{
			ip->id_string = ft_charjoin(ip->id_string, ip->ch);
			if (ip->ch == '{')
				check_token2_sub(line, ip, '}');
			else if (ip->ch == '(')
				check_token2_sub(line, ip, ')');
			ip->id_string = ft_charjoin(ip->id_string, ip->ch);
		}
	}
	else if (ip->ch == '\\')
	{
		next_ch(*line, ip);
		ip->id_string = ft_charjoin(ip->id_string, ip->ch);
	}
}

void check_token(char **line, t_ip *ip)
{
	char *line2;

	if (ip->ch == '|')
	{
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
	else if (ip->ch == '>') {
		if (next_ch(*line, ip) == '>')
		{
			ip->id_string = ft_charjoin(ip->id_string, ip->ch);
			next_ch(*line, ip);
			ip->sy = DGT;
		}
		else
			ip->sy = GT;
	}
	else if (ip->ch == '<')
	{
		next_ch(*line, ip);
		ip->sy = LT;
	}
	else if (ip->ch == ';')
	{
		next_ch(*line, ip);
		ip->sy = SEMICOLON;
	}
}

void get_token(char **line, t_ip *ip)
{
	/* init */
	//free(ip->id_string);
	ip->id_string = ft_calloc(sizeof(char), 1);

	/* skip blank */
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(*line, ip);

	/* End of Input */
	if (ip->ch == '\0')
		ip->sy = INPUT_END;
	else
	{
		if (ft_strchr("|><;", ip->ch) == NULL)
		{
			while (ft_strchr("|><; \0", ip->ch) == NULL)
			{
				if (ft_strchr("\"\'\\$", ip->ch) != NULL)
					check_token2(line, ip);
				else
					ip->id_string = ft_charjoin(ip->id_string, ip->ch);
				next_ch(*line, ip);
			}
			ip->sy = IDENTIFY;
		}
		else
		{
			ip->id_string = ft_charjoin(ip->id_string, ip->ch);
			check_token(line, ip);
		}
	}
	/* To debug 
	while (ip->sy != INPUT_END)
	{
		printf("[%s]:%s\n", ip->id_string,command_name[ip->sy]); 
		get_token(line, ip);
	}
	*/
	return;
}

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

void parse_line(char *line)
{
	t_ip ip;
	char ***args;

	set_signal(SIGINT);
	//printf("line:[%s]\n", line);
	ip.id_string = malloc(1);
	ip.ch = ' ';
	ip.index = 0;
	get_token(&line, &ip);
	args = (char ***)ft_calloc3(sizeof(char **), 1);
	input(&line, &ip, &args);
	exit(0);
}
