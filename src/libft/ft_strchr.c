#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;

	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	t = (char *)s;
	while (*t != '\0')
	{
		if (*t == (char)c)
			return (t);
		t++;
	}
	return (NULL);
}
