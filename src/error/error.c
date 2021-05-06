#include "../../includes/minishell.h"

void err_syntax(t_ip *ip, t_shell *shell)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	if (*ip->id_string == '\0')
		ft_putendl_fd("`newline'", 2);
	else
		ft_putendl_fd(ip->id_string, 2);
	shell->exit_status = 258;
}

void err_notfound(char *cmd, t_shell *shell)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	shell->exit_status = 127;
	minishell_end(shell);
}

void err_badfd(int n, t_shell *shell)
{
	ft_putnbr_fd(n, 2);
	ft_putendl_fd(": Bad file descriptor", 2);
	shell->exit_status = 1;
}

void err_errno(char *s, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void err_cstmmsg(char *s, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}
