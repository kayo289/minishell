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

static void print_env(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_strchr("\'\"\\$`",str[i]) != NULL)
			ft_putstr_fd("\\", 1);
		ft_putchar_fd(str[i], 1);
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
		if (ft_strchr(tab[i], '=') == NULL)
			ft_putendl_fd(tab[i], 1);
		else
		{
			str = ft_split(tab[i], '=');
			ft_putstr_fd(str[0], 1);
			ft_putstr_fd("=\"", 1);
			if (str[1] != NULL)
			{
				j = 1;
				print_env(str[j++]);
				while (str[j] != NULL)
				{
					ft_putstr_fd("=", 1);
					ft_putstr_fd(str[j++], 1);
				}
			}
			ft_putendl_fd("\"", 1);
			dp_free(str);
		}
		i++;
	}
	free(tab);
}
/*
static void identifier_err(char *s, char *c, char *msg, t_shell *shell)
{

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(msg, 2);
	shell->exit_status = 1;
}
*/

int minishell_export(char **argv, t_shell *shell)
{
	char *name;
	char status;
	int i;

	status = 0;
 	if (argv[1] == NULL)
		show_env();
	else
	{
		i = 1;
		while (argv[i] != NULL)
		{
			if (!ft_isalpha(argv[i][0]) && !(argv[i][0] == '_' && ft_isalpha(argv[i][1])))
			{
				//identifier_err("export", argv[i], "not a valid identifier", shell);
				err_cstmmsg("export", argv[i], "not a valid identifier");
				status = 1;
			}
			if (ft_strchr(argv[i], '=') != NULL)
				set_shell_var(shell, argv[i]);
			name = get_param_name(argv[i]);
			set_environ(shell, name);
			free(name);
			i++;
		}
	}
	return (status);
}
