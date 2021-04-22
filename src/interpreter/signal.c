#include "../../includes/minishell.h"

static void sigint(int p_signame)
{
	ft_putendl_fd("\b\b  ", 1);
	(void)p_signame;
}

static void sigquit(int p_signame)
{
	ft_putendl_fd("Quit (core dumped)", 1);
	(void)p_signame;
}

void set_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (signal(SIGINT, sigint) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	if (signal(SIGQUIT, sigquit) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

