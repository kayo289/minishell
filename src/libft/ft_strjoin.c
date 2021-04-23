#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
