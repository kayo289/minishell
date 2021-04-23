#include "../../includes/libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)buf)[i] == (unsigned char)ch)
			return ((void *)(buf + i));
		i++;
	}
	return (NULL);
}
