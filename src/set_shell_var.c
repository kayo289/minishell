#include "../includes/minishell.h"

int set_shell_var(char *name, char *value, char ***shell_var)
{
	char **str;
	char *parameter;
	int i;

	i = 0;
	if (name == NULL || ft_strchr(name, '=') != NULL)
		return (-1);
	parameter = ft_strjoin(name, "=");
	parameter = ft_strjoin(parameter, value);
	while ((*shell_var)[i] != NULL)
	{
		str = ft_split((*shell_var)[i], '=');
		if (ft_strcmp(str[0], name) == 0)
		{
			(*shell_var)[i] = parameter;
			return (0);
		}
		i++;
	}
	*shell_var = ft_realloc2(*shell_var, parameter);
	return (0);
}
