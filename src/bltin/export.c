#include "../../includes/minishell.h"

static void bubble_sort(char **tab, int n)
{
	char *temp;
	int i;
	int j;

	i = 0;
	while (i < n - 1)
	{
		j = n - 1;
		while (j > i)
		{
			if (ft_strcmp(tab[j], tab[j - 1]) < 0)
			{
				temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
			}
			j--;
		}
		i++;
	}
}

static void show_env(void)
{
	extern char **environ;
	char **tab;
	char **str;
	int i;
	int j;

	tab = ft_calloc2(sizeof(char **), 1);
	i = 0;
	while (environ[i] != NULL)
	{
		tab = ft_realloc2(tab, environ[i]);
		i++;
	}
	bubble_sort(tab, i);
	i = 0;
	while (tab[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		str = ft_split(tab[i], '=');
		ft_putstr_fd(str[0], 1);
		if (str[1] != NULL)
		{
			j = 1;
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(str[j++], 1);
			while (str[j] != NULL)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd(str[j++], 1);
			}
			ft_putstr_fd("\"", 1);
		}
		ft_putendl_fd("", 1);
		dp_free(str);
		i++;
	}
	free(tab);
}

int minishell_export(char **argv, t_shell *shell)
{
	char **str;
	char *value;
	int i;

 	if (argv[1] == NULL)
		show_env();
	else
	{
		i = 1;
		while (argv[i] != NULL)
		{
			if (ft_strchr(argv[i], '=') != NULL)
				set_shell_var(shell, argv[i]);
			str = ft_split(argv[i], '=');
			value = get_shell_var(shell, str[0]);
			if (value == NULL)
				value = "";
			//ft_setenv(str[0], value);
			setenv(str[0], value, 1);
			dp_free(str);
			i++;
		}
	}
	return (0);
	setenv(str[0], value, 1);
}
