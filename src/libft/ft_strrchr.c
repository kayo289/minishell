#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}
