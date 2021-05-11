#include "../../includes/minishell.h"

static char next(t_dlist **word)
{
	char ch;

	if (*word != NULL)
	{
		ch = ((char *)(*word)->content)[0];
		*word = (*word)->next;
	}
	else
		ch = '\0';
	return ch;
}

static void brace(t_dlist **word, char **key)
{
	char ch;

	while ((ch = next(word)) != '}')
	{
		if (ch == '\0')
			break;
		else
			ft_charjoin(key, ch);
	}
	next(word);
}

char *parameter(t_dlist **word, t_shell *shell)
{
	char *key;
	char *val;
	char ch;

	key = ft_calloc(sizeof(char), 1);
	ch = next(word);
	if (ch == '?')
	{
		next(word);
		return (ft_itoa(shell->exit_status));
	}
	if (!ft_issnack_case(ch))
		return (ft_strdup("$"));
	if (ch == '{')
		brace(word, &key);
	else
	{
		while (ft_issnack_case(ch))
		{
			ft_charjoin(&key, ch);
			ch = next(word);
		}
	}
	val = getenv(key);
	free(key);
	return (val);
}

static void dollar(t_dlist **word, char **arg, char ***args, t_shell *shell)
{
	char *val;
	char *str;
	char *tmp;

	val = parameter(word, shell);
	if (val == NULL)
		return;
	str = ft_strtrim(val, " \t\n");
	if (ft_strchr(" \t\n", val[0]) != NULL)
	{
		if (**arg != '\0')
		{
			*args = ft_realloc2(*args, *arg);
			*arg = ft_calloc(sizeof(char), 1);
		}
	}
	tmp = *arg;
	*arg = ft_strjoin(*arg, str);
	free(tmp);
	if (ft_strchr(" \t\n", val[ft_strlen(val) - 1]) != NULL)
	{
		if (**arg != '\0')
		{
			*args = ft_realloc2(*args, *arg);
			*arg = ft_calloc(sizeof(char), 1);
		}
	}
	free(str);
}

static void double_quote(t_dlist **word, char **arg, char ***args, t_shell *shell)
{
	char ch;

	ch = next(word);
	while (ch != '\"')
	{
		if (ch == '$')
			dollar(word, arg, args, shell);
		else if (ch == '\\')
		{
			if (ft_strchr("$`\"\\", ch) == NULL)
				ft_charjoin(arg, '\\');
			ft_charjoin(arg, ch);
		}	
		else
			ft_charjoin(arg, ch);
		ch = next(word);
	}
}

static void single_quote(t_dlist **word, char **arg)
{
	char ch;

	ch = next(word);
	while (ch != '\'')
	{
		ft_charjoin(arg, ch);
		ch = next(word);
	}
}

static void escape(t_dlist **word, char **arg)
{
	char ch;

	ch = next(word);
	ft_charjoin(arg, ch);
}

char **expansion(t_list *words, t_shell *shell)
{
	char	**args;
	char	*arg;
	t_dlist	*word;
	char	ch;

	args = ft_calloc2(sizeof(char), 1);
	while (words != NULL)
	{
		arg = ft_calloc(sizeof(char), 1);
		word = (t_dlist*)words->content;
		while (word != NULL)
		{
			ch = next(&word);
			while (ch == ' ')
				ch = next(&word);
			if (ch == '\'')
				single_quote(&word, &arg);
			else if (ch == '\"')
				double_quote(&word, &arg, &args, shell);
			else if (ch == '\\')
				escape(&word, &arg);
			else if (ch == '$')
				dollar(&word, &arg, &args, shell);
			else if (ch != ';')
				ft_charjoin(&arg, ch);
		}
		args = ft_realloc2(args, arg);
		words = words->next;
	}
	return (args);
}
