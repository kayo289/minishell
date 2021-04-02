#include "../../includes/libft.h"

int	ft_issnack_case(int n)
{
	if (ft_isalpha(n) || n == '_' || ft_isalnum(n))
		return (1);
	return (0);
}
