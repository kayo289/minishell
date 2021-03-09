#include "../includes/minishell.h"

void error(char *message, char *token)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(token, 2);
	exit(1);
}

void error2(char *message, char token)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd(token, 2);
	ft_putchar_fd('\n', 2);
}
