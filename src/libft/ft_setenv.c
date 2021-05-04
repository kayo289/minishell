#include "../../includes/libft.h"

static char **last_environ;

static void add_to_environ(char *param)
{
	extern char	**environ;
	char		**new_environ;
	int			size;

	size = 0;
	while (environ[size] != NULL)
		size++;
	new_environ = (char **)ft_calloc((size + 2), sizeof(char *));
	ft_memcpy(new_environ, environ, sizeof(char*) * size);
	new_environ[size] = param;
	environ = new_environ;
	last_environ = environ;
}

int	ft_setenv(char *name, char *value)
{
	extern char	**environ;
	char		**ep;
	char		*new_value;
	size_t		namelen;
	char		*tmp;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	namelen = ft_strlen(name);
	tmp = ft_strjoin(name, "=");
	new_value = ft_strjoin(tmp, value);
	free(tmp);
	ep = environ;
	while (*ep != NULL)
	{
		if (!ft_strncmp(*ep, name, namelen) && (*ep)[namelen] == '=')
		{
			free(*ep);
			*ep = new_value;
			return (0);
		}
		ep++;
	}
	add_to_environ(new_value);
	return (0);
}
