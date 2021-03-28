#include "../../includes/libft.h"

int	ft_issnack_case(int n)
{
	if ((n >= 'a' && n <= 'z') || (n >= 'A' && n <= 'Z') || n == '_' || ft_isalnum(n))
		return (1);
	return (0);
}
