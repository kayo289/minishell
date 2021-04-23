#include "../../includes/libft.h"

void	*ft_memset(void *buf, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)buf)[i] = (char)c;
		i++;
	}
	return (buf);
}
