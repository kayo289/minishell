#include "../../includes/libft.h"

void	ft_charjoin(char **old, char c)
{
	char	*new;
	int		len;
	int		i;

	if (*old == NULL)
		*old = ft_calloc(sizeof(char), 1);
	len = ft_strlen(*old);
	new = (char *)malloc(sizeof(char) * (len + 2));
	i = -1;
	while (++i < len)
		new[i] = (*old)[i];
	new[i++] = c;
	new[i] = '\0';
	free(*old);
	*old = new;
}
