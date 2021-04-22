#include "../../includes/libft.h"

char	**ft_realloc2(char **old, char *add)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	while (old[len] != NULL)
		len++;
	new = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = add;
	new[i] = NULL;
	return (new);
}
