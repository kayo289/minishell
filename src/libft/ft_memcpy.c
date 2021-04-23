#include "../../includes/libft.h"

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	if (!buf1 && !buf2)
		return (NULL);
	while (n--)
		((char *)buf1)[n] = ((char *)buf2)[n];
	return (buf1);
}
