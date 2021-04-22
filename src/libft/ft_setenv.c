#include "../../includes/libft.h"

int	ft_setenv(char *name, char *value)
{
	extern char	**environ;
	char		**str;
	char		*parameter;
	int			i;

	i = 0;
	if (name == NULL || ft_strchr(name, '=') != NULL)
		return (-1);
	parameter = ft_strjoin(name, "=");
	parameter = ft_strjoin(parameter, value);
	while (environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (ft_strcmp(str[0], name) == 0)
		{
			environ[i] = parameter;
			return (0);
		}
		i++;
	}
	environ = ft_realloc2(environ, parameter);
	return (0);
}
