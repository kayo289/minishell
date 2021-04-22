#include "../../includes/libft.h"

char	***ft_calloc3(size_t nmemb, size_t size)
{
	char	***ret;
	size_t	i;

	ret = (char ***)malloc(nmemb * size);
	i = 0;
	while (i < size)
	{
		ret[i] = NULL;
		i++;
	}
	return (ret);
}
