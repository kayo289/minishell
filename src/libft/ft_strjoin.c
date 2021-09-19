#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*str;

	if (s1 == NULL)
		return (ft_strdup((char*)s2));
	else if (s2 == NULL)
		return (ft_strdup((char*)s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
