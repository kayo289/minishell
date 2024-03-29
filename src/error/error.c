#include "../../includes/minishell.h"

void err_syntax(t_ip *ip, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	if (ip->id_string[0] == '\0')
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(ip->id_string, 2);
	ft_putendl_fd("\'", 2);
	shell->exit_status = 258;
}

void err_notfound(char *cmd, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	shell->exit_status = 127;
	minishell_end(shell);
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

void err_cstmmsg(char *s, char *c, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	if (c != NULL)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("\': ", 2);
	}
	ft_putendl_fd(msg, 2);
}
