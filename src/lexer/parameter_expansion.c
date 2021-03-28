#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void brace(t_dlist **line, char **key)
{
	char ch;
	t_dlist **line2;
	
	line2 = NULL;
	*line = (*line)->next;
	ch = ((char*)(*line)->content)[0];
	while (ch != '}')
	{
		if (ch == '\0')
		{
			prompt("> ", line2);
			ft_dlstadd_back(line, ft_dlstnew("\n"));
			ft_dlstadd_back(line, *line2);
			/*
			write(1, "> ", 2);
			if (get_next_line(0, &line2) == 0)
			{
				error2(MESSAGE1, '}');
				error2(MESSAGE2, '\0');
				exit(1);
			}
			*line = ft_strjoin(*line, "\n");
			*line = ft_strjoin(*line, line2);
			*/
		}
		else
			ft_charjoin(key, ch);
		*line = (*line)->next;
		ch = ((char*)(*line)->content)[0];
	}
	*line = (*line)->next;
}

char *expand_parameter(t_dlist **line)
{
	char *key;
	char *val;
	char ch;

	key = ft_calloc(sizeof(char), 1);
	ch = ((char*)(*line)->content)[0];
	if (ch == '{')
		brace(line, &key);
	else
	{
		//while (ft_isalpha((*line)[ip->index]) || (*line)[ip->index] == '_')
		while (ft_issnack_case(ch))
		{
			ft_charjoin(&key, ch);
			*line = (*line)->next;
			ch = ((char*)(*line)->content)[0];
		}
	}
	val = ft_getenv(key);
	return (val);
}

