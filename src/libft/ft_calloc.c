#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ans;
	size_t	total;

	total = count * size;
	ans = malloc(total);
	if (!ans)
		return (NULL);
	ft_memset(ans, 0, total);
	return (ans);
}
