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
	set_signal_ign();
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

void set_signal_ign(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

void set_signal_dfl(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

