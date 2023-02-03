#include "../../includes/minishell.h"

int	minishell_pwd(t_shell *shell)
{
	if (!shell->pwd)
		shell->pwd = getcwd(NULL, 0);
	if (shell->pwd)
		ft_putendl_fd(shell->pwd, 1);
	return (0);
}
