#include "../../includes/libft.h"

static char	**get_env_adress(char *name)
{
	extern char	**environ;
	int			i;
	char		**str;

	i = 0;
	while (environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (ft_strcmp(str[0], name) == EQUAL)
			return (&environ[i]);
		i++;
	}
	return (NULL);
}

int	ft_unsetenv(char *name)
{
	extern char	**environ;
	char		**adress;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (FAIL);
	}
	adress = get_env_adress(name);
	if (adress != NULL)
	{
		while (*adress)
		{
			*adress = *(adress + 1);
			adress++;
		}
		adress++;
	}
	return (0);
}
