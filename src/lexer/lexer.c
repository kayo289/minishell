#include "../../includes/minishell.h"

char next_ch(char *line, t_ip *ip)
{
	ip->ch = line[ip->index];
	if (line[ip->index] != '\0')
		ip->index++;
	return (ip->ch);
}

static void save_token(t_ip *ip, t_queue *tokens)
{
	t_list	*lst;
	t_ip	*tmp;

	tmp = malloc(sizeof(t_ip));
	*tmp = *ip;
	lst = ft_lstnew(tmp);
	ft_lstadd_back(tokens, lst);
	ip->id_string = ft_calloc(sizeof(char), 1);
}

static void dollar(line, ip, tokens)
	char **line; t_ip *ip; t_queue *tokens;
{
	char *val;
	char *str;

	if ((val = expand_parameter(line, ip)) == NULL)
		return;
	str = ft_strtrim(val, " \t\n");
	if (ft_strchr(" \t\n", val[0]) != NULL) {
		if (ft_strcmp(ip->id_string, "") != 0)
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
	ip->id_string = ft_strjoin(ip->id_string, str);
	if (ft_strchr(" \t\n", val[ft_strlen(val) - 1]) != NULL)
	{
		if (ft_strcmp(ip->id_string, "") != 0)
		{
			ip->sy = IDENTIFY;
			save_token(ip, tokens);
		}
	}
}

static void get_token(line, ip, tokens, sv)
	char **line; t_ip *ip; t_queue *tokens; t_shell_var *sv;
{
	while (ip->ch == ' ' || ip->ch == '\t')
		next_ch(*line, ip);
	if (ip->ch == '\0')
	{
		ip->sy = INPUT_END;
		return;
	}
	if (ft_strchr("|><;", ip->ch) == NULL)
	{
		while (ft_strchr("|><; \0", ip->ch) == NULL)
		{
			if (ft_strchr("$", ip->ch) != NULL)
				dollar(line, ip, tokens, sv);
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
	save_token(ip, tokens);
	get_token(line, ip, tokens, sv);
}

void lexer(char *line, t_queue *tokens, t_shell_var *sv)
{
	t_ip	ip;

	ip.ch = ' ';
	ip.index = 0;
	ip.id_string = ft_calloc(sizeof(char), 1);
	*tokens = NULL;
	get_token(&line, &ip, tokens, sv);
	save_token(&ip, tokens);
}
