#include "../../includes/minishell.h"

static char now_word(char **word)
{
	return (**word);
}

static char next_word(char **word)
{
	if (**word != '\0')
		(*word)++;
	return **word;
}

static void brace(char **word, char **key)
{
	char ch;

	ch = next_word(word);
	while (ch != '}')
	{
		if (ch == '\0')
			break;
		else
			ft_charjoin(key, ch);
		ch = next_word(word);
	}
	next_word(word);
}

char *parameter(char **word, t_shell *shell)
{
	char *key;
	char *val;
	char ch;

	key = ft_calloc(sizeof(char), 1);
	ch = next_word(word);
	if (ch == '{')
		brace(word, &key);
	else
	{
		if (ch == '?')
		{
			next_word(word);
			return (ft_itoa(shell->exit_status));
		}
		if (!ft_issnack_case(ch))
			return (ft_strdup("$"));
		while (ft_issnack_case(ch))
		{
			ft_charjoin(&key, ch);
			ch = next_word(word);
		}
	}
	val = getenv(key);
	free(key);
	return (val);
}

static void dollar(char **word, char **arg, char ***args, t_shell *shell)
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
		if (*arg != NULL)
		{
			*args = ft_realloc2(*args, *arg);
			*arg = NULL;
		}
	}
	tmp = *arg;
	*arg = ft_strjoin(*arg, str);
	free(tmp);
	if (ft_strchr(" \t\n", val[ft_strlen(val) - 1]) != NULL)
	{
		if (*arg != NULL)
		{	
			*args = ft_realloc2(*args, *arg);
			*arg = NULL;
		}
	}
	free(str);
}

static bool is_closed(char *word, char **arg)
{
	char ch;
	char end_ch;

	ch = next_word(&word);
	end_ch = now_word(&word);
	while (ch != end_ch)
	{
		if (ch == '\0')
		{
			ch = now_word(&word);
			ft_charjoin(arg, ch);
			return false;
		}
		ch = next_word(&word);
	}
	return true;
}

static void double_quote(char **word, char **arg, char ***args, t_shell *shell)
{
	char ch;

	*arg = ft_strjoin(*arg, "");
	is_closed(*word, arg);
	ch = next_word(word);
	while (ch != '\"')
	{
		if (ch == '\0')
			break;
		if (ch == '$')
		{
			dollar(word, arg, args, shell);
			ch = now_word(word);
		}
		else
		{
			ft_charjoin(arg, ch);
			ch = next_word(word);
		}
	}
	next_word(word);
}

static void single_quote(char **word, char **arg, char ***args, t_shell *shell)
{
	char ch;
	bool quote;

	*arg = ft_strjoin(*arg, "");
	quote = is_closed(*word, arg);
	ch = next_word(word);
	while (ch != '\'')
	{
		if (ch == '\0')
			break;
		if (ch == '$' && !quote)
		{
			dollar(word, arg, args, shell);
			ch = now_word(word);
		}
		else
		{
			ft_charjoin(arg, ch);
			ch = next_word(word);
		}
	}
	next_word(word);
}

char **expand_word(char *word, t_shell *shell, bool quote)
{
	char **args;
	char *arg;
	char ch;

	args = ft_calloc2(sizeof(char*), 1);
	arg = NULL;
	ch = now_word(&word);
	while (*word != '\0')
	{
		while (ch == ' ')
			ch = next_word(&word);
		if (quote && ch == '\'')
			single_quote(&word, &arg, &args, shell);
		else if (quote && ch == '\"')
			double_quote(&word, &arg, &args, shell);
		else if (ch == '$')
			dollar(&word, &arg, &args, shell);
		else
		{
			ft_charjoin(&arg, ch);
			ch = next_word(&word);
		}
		ch = now_word(&word);
	}
	if (arg != NULL)
		args = ft_realloc2(args, arg);
	return args;
}

char **expand_words(t_list *words, t_shell *shell, bool quote)
{
	char	**args;
	char	**ret;
	int		i;

	args = ft_calloc2(sizeof(char), 1);
	while (words != NULL)
	{
		ret = expand_word(words->content, shell, quote);
		i = 0;
		while (ret[i] != NULL)
		{
			args = ft_realloc2(args, ret[i]);
			i++;
		}
		words = words->next;
	}
	return (args);
}
