#include "../includes/minishell.h"

bool equal(char *s, char *t)
{
	if (ft_strlen(s) != ft_strlen(t))
		return (false);
	else if (ft_strncmp(s, t, ft_strlen(s)) == 0)
		return (true);
	return (false);
}

