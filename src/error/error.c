#include "../../includes/minishell.h"

void err_syntax(t_ip **ip, t_shell *shell)
{
	ft_putstr_fd("syntax error near unexpected token ", 2); 
	if (*(*ip)->id_string == '\0')
		ft_putendl_fd("`newline'", 2);
	else
		ft_putendl_fd((*ip)->id_string, 2);
	(*shell)->exit_status = 258;
}

void err_notfound(char *cmd, t_shell *shell)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	(*shell)->exit_status = 127;
	exit(127);
}

void err_badfd(int n, t_shell *shell)
{
	ft_putnbr_fd(n, 2);
	ft_putendl_fd(": Bad file descriptor", 2);
	(*shell)->exit_status = 1;
	exit(1);
}	
