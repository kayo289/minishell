#include "../../includes/libft.h"

int	ft_isalnum(int n)
{
	if (ft_isalpha(n) || ft_isdigit(n))
		return (1);
	return (0);
}
