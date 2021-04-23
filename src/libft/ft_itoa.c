#include "../../includes/libft.h"

static unsigned int	ft_abs(int n)
{
	unsigned int	nbr;

	if (n < 0)
		nbr = (unsigned int) - n;
	else
		nbr = n;
	return (nbr);
}

static size_t	calc_degit(unsigned int n)
{
	if (n >= 10)
		return (1 + calc_degit(n / 10));
	return (1);
}

static int	judge_minus(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char	*ans;
	size_t	len;
	size_t	is_minus;
	size_t	nb;

	is_minus = judge_minus(n);
	nb = ft_abs(n);
	len = calc_degit(nb) + is_minus;
	ans = ft_calloc(len + 1, sizeof(char));
	if (!ans)
		return (NULL);
	ans[len] = '\0';
	while (len-- > is_minus)
	{
		ans[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (is_minus)
		ans[len] = '-';
	return (ans);
}
