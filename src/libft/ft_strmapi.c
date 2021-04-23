#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ans;
	unsigned int	len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ans = ft_calloc(len + 1, sizeof(char));
	if (!ans)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
