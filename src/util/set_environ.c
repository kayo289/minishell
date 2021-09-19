#include "../../includes/minishell.h"

static void add_to_environ(char *param)
{
	extern char	**environ;
	static char	**last_environ;
	char		**new_environ;
	int			size;
	int			i;

	size = 0;
	while (environ[size] != NULL)
		size++;
	new_environ = ft_calloc2(sizeof(char *), (size + 2));
	i = 0;
	while (i < size)
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[size] = param;
	if (environ == last_environ)
		free(environ);
	environ = new_environ;
	last_environ = environ;
}

void set_environ(t_shell *shell, char *name)
{
	extern char	**environ;
	char		**ep;
	char		*param;

	param = get_shell_var(shell, name);
	if (param == NULL)
		add_to_environ(ft_strdup(name));
	else
	{
		ep = environ;
		while (*ep != NULL)
		{
			if (!ft_strncmp(*ep, name, ft_strlen(name)))
			{
				*ep = param;
				return ;
			}
			ep++;
		}
		add_to_environ(param);
	}
}
