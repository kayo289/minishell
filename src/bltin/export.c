#include "../../includes/libcmds.h"

static void bubble_sort(void)
{
	extern char **environ;
	char *temp;
	int i;
	int j;
	int n;

	n = 0;
	while (environ[n] != NULL)
		n++;
	i = 0;
	while (i < n - 1)
	{
		j = n - 1;
		while (j > i) 
		{
			if (ft_strcmp(environ[j], environ[j - 1]) < 0)
			{
				temp = environ[j - 1];
				environ[j - 1] = environ[j];
				environ[j] = temp;
			}
			j--;
		}
		i++;
	}
}

static void show_env(void)
{
	extern char **environ;
	int i;

	bubble_sort();
	i = 0;
	while (environ[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(environ[i], 1);
		i++;
	}
}

int minishell_export(char **argv, t_shell *shell)
{
	char **str;
	char *value;
	int i;
 
 	if (argv[1] == NULL)
	{
		show_env();
		return (0);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '=') != NULL)
			set_shell_var(*shell, argv[i]);
		str = ft_split(argv[i], '=');
		value = get_shell_var(*shell, str[0]);
		ft_setenv(str[0], value);
		free(str);
		i++;
	}
	return (0);
}
