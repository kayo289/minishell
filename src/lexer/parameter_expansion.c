#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

static void replace(char **line, char start, int size, char *val)
{
	char *res;
	int res_len;

	res_len = ft_strlen(*line) + ft_strlen(val) - size;
	res = ft_calloc(sizeof(char), res_len + 1);

	ft_strlcpy(res, *line, start);
	ft_strlcat(res, val, res_len + 1);
	ft_strlcat(res, *line + start + size, res_len + 1);
	*line = res;
}

static int line_continuation(char **line, char *str, char **key)
{
	char *line2;
	int size; 
	
	size = 1;
	while (*str != '}')
	{
		if (*str == '\0')
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
			ft_charjoin(key, *str);
		str++;
		size++;
	}
	size++;
	return (size);
}

void parameter_expansion(char **line, t_ip *ip)
{
	char *key;
	char *val;
	int i;
	int size;

	key = ft_calloc(sizeof(char), 1);
	i = ip->index;
	if ((*line)[i] == '{')
		size = line_continuation(line, &(*line)[i + 1], &key);
	else
	{
		while (ft_strchr(" \"\'`><|;&${}[]()!?\0", (*line)[i]) == NULL)
			ft_charjoin(&key, (*line)[i++]);
		size = i - ip->index;
	}
	val = ft_getenv(key);
	val = ft_strjoin("\"", val);
	val = ft_strjoin(val, "\"");
	replace(line, ip->index, size, val);
	ip->index--;
}

