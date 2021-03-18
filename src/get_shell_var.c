#include "../includes/minishell.h"

char *get_shell_var(char *name, char ***shell_var)
{
	char **str;
	char  *value;
	int	i;
	int j;

	value = (char *)ft_calloc(sizeof(char), 1);
	i = 0;
	while ((*shell_var)[i] != NULL) 
	{
		str = ft_split((*shell_var)[i], '=');
		if (ft_strcmp(str[0], name) == 0)
		{
			j = 1;
			while (str[j] != NULL)
			{
				value = ft_strjoin(value, str[j]);
				j++;
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}
