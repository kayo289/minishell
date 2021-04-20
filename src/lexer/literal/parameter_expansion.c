#include "../../../includes/minishell.h"

static void brace(t_dlist **line, char **key)
{
	char ch;
	//t_dlist **line2;
	
	//line2 = NULL;
	*line = (*line)->next;
	ch = ((char*)(*line)->content)[0];
	while (ch != '}')
	{
		/*
		if (ch == '\0')
		{
			prompt("> ", line2, shell);
			ft_dlstadd_back(line, ft_dlstnew("\n"));
			ft_dlstadd_back(line, *line2);
		}
		else
			*/
			ft_charjoin(key, ch);
		*line = (*line)->next;
		ch = ((char*)(*line)->content)[0];
	}
	*line = (*line)->next;
}

char *expand_parameter(t_dlist **line, t_ip *ip, t_queue *tokens)
{
	char *key;
	char *val;
	char ch;

	key = ft_calloc(sizeof(char), 1);
	ch = ((char*)(*line)->content)[0];
	if (ch == '\0')
	{
		ft_charjoin(&ip->id_string, '$');
		save_token(ip, tokens);
		return (NULL);
	}
	if (ch == '{')
		brace(line, &key);
	else
	{
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

