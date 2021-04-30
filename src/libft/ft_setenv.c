#include "../../includes/libft.h"

static void dp_free(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void add_to_environ(char *param)
{
	extern char	**environ;
	char		**new_environ;
	int			size;

	size = 0;
	while (environ[size] != NULL)
		size++;
	new_environ = ft_calloc2(sizeof(char *), 1);
	ft_memcpy(new_environ, environ, size * sizeof(char *));
	new_environ[size] = param;
	new_environ[size + 1] = param;
	environ = new_environ;
}

int	ft_setenv(char *name, char *value)
{
	extern char	**environ;
	char		**str;
	char		*param;
	int			len;
	int			i;

	if (name == NULL || ft_strchr(name, '=') != NULL)
		return (-1);
	len = ft_strlen(name) + ft_strlen(value) + 1;
	param = ft_calloc(sizeof(char), len + 1);
	ft_strlcat(param, name, len + 1);
	ft_strlcat(param, "=", len + 1);
	ft_strlcat(param, value, len + 1);
	i = 0;
	while (environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (ft_strcmp(str[0], name) == 0)
		{
			dp_free(str);
			environ[i] = param;
			return (0);
		}
		dp_free(str);
		i++;
	}
	add_to_environ(param);
	return (0);
}
