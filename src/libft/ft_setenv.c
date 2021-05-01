#include "../../includes/libft.h"

static void add_to_environ(char *param)
{
	extern char	**environ;
	char		**new_environ;
	int			size;
	int			i;

	size = 0;
	while (environ[size] != NULL)
		size++;
	new_environ = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (environ[i] != NULL)
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[i] = param;
	new_environ[i + 1] = NULL;
	environ = new_environ;
}

int	ft_setenv(char *name, char *value)
{
	extern char	**environ;
	char		**ep;
	char		*new_value;
	size_t		namelen;
	size_t		vallen;	
	size_t		varlen;	

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	namelen = ft_strlen(name);
	vallen = ft_strlen(value) + 1;
	varlen = namelen + 1 + vallen;
	new_value = (char *)malloc(sizeof(char) * varlen);
	ft_memcpy(new_value, name, namelen);
	ft_memcpy(&new_value[namelen], "=", 1);
	ft_memcpy(&new_value[namelen + 1], value, vallen);
	ep = environ;
	while (*ep != NULL)
	{
		if (!ft_strncmp(*ep, name, namelen) && (*ep)[namelen] == '=')
		{
			*ep = new_value;
			return (0);
		}
		ep++;
	}
	add_to_environ(new_value);
	return (0);
}
