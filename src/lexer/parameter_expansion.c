#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void brace(char **line, t_ip *ip, char **key)
{
	char *line2;
	
	while ((*line)[++ip->index] != '}')
	{
		if ((*line)[ip->index] == '\0')
		{
			write(1, "> ", 2);
			if (get_next_line(0, &line2) == 0)
			{
				error2(MESSAGE1, '}');
				error2(MESSAGE2, '\0');
				exit(1);
			}
			*line = ft_strjoin(*line, "\n");
			*line = ft_strjoin(*line, line2);
		}
		else
			ft_charjoin(key, (*line)[ip->index]);
	}
	ip->index++;
}

char *expand_parameter(char **line, t_ip *ip, t_shell_var sv)
{
	char *key;
	char *val;

	key = ft_calloc(sizeof(char), 1);
	if ((*line)[ip->index] == '{')
		brace(line, ip, &key);
	else
	{
		while (ft_isalpha((*line)[ip->index]))
			ft_charjoin(&key, (*line)[ip->index++]);
	}
	val = get_shell_var(sv, key);
	return (val);
}

