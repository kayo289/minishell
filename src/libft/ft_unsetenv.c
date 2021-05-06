#include "../../includes/libft.h"

static void dp_free(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

static char	**get_env_adress(char *name)
{
	extern char	**environ;
	char		**str;
	int			i;

	i = 0;
	while (environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (ft_strcmp(str[0], name) == EQUAL)
		{
			dp_free(str);
			return (&environ[i]);
		}
		dp_free(str);
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
		while (*adress != NULL)
		{
			*adress = *(adress + 1);
			adress++;
		}
	}
	return (0);
}
