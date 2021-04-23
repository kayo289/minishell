#include "../../includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] && n > 0)
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j] && j < (int)n)
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		i++;
		n--;
	}
	return (NULL);
}
