#include "../../includes/libft.h"

static int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

long long	ft_atoi(const char *str)
{
	int			i;
	int			minus;
	unsigned long long	ans;

	ans = 0;
	minus = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		ans = ans * 10 + (str[i++] - '0');
		if (ans > LLONG_MAX && minus == 1)
		{
			errno = ERANGE;
			return (LLONG_MAX);
		}else if (ans - 1 > LLONG_MAX && minus == -1)
		{
			errno = ERANGE;
			return ((LLONG_MIN));
		}
	}
	return (ans * minus);
}
