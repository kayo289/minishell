#include "../../includes/libft.h"

static int equal(char *s, char *t)
{
	if (ft_strlen(s) != ft_strlen(t))
		return (0);
	else if (ft_strncmp(s, t, ft_strlen(s)) == 0)
		return (1);
	return (0);
}

int ft_setenv(char *name, char *value)
{
	extern char **environ;
	char **str;
	char *parameter;
	int i;

	i = 0;
	if (name == NULL || ft_strchr(name, '=') != NULL)
		return (-1);
	parameter = ft_strjoin(name, "=");
	parameter = ft_strjoin(parameter, value);
	while (environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (equal(str[0], name) == 1)
		{
			environ[i] = parameter;
			return (0);
		}
		i++;
	}
	environ[i] = ft_strdup(parameter);
	environ[i + 1] = NULL;
	return (0);
}
