#include "../../includes/libft.h"

char *ft_getenv(char *key)
{
	extern char **environ;
	char **str;
	char  *value;
	int	i;
	int j;

	value = (char *)ft_calloc(sizeof(char), 1);
	i = 0;
	while (environ[i] != NULL) 
	{
		str = ft_split(environ[i], '=');
		if (ft_strcmp(str[0], key) == 0)
		{
			j = 1;
			while (str[j] != NULL)
			{
				value = ft_strjoin(value, str[j]);
				j++;
			}
		}
		i++;
	}
	return (value);
}
