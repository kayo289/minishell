#include "../../includes/minishell.h"

static bool check_operator(t_gmr *gmr, t_shell *shell)
{
	if (gmr->op == ANDAND_OP)
	{
		if (shell->exit_status != 0)
			return (false);
	}
	else if (gmr->op == OROR_OP)
	{
		if (shell->exit_status == 0)
			return (false);
	}
	else if (gmr->op == SEMICOLON_OP)
	{
		if (shell->exit_status != 0)
			return (false);
	}
	return (true);
}

static void set_stdfd(t_stdfd *stdfd)
{
	stdfd->in = dup(0);
	stdfd->out = dup(1);
	stdfd->err = dup(2);
}

static void get_stdfd(t_stdfd *stdfd)
{
	dup2(stdfd->in, 0);
	dup2(stdfd->out, 1);
	dup2(stdfd->err, 2);
}

void interpreter(t_list *gmrs, t_shell *shell)
{
	int		pfd[2];
	t_gmr	*gmr;
	bool	run;
	t_stdfd	stdfd;

	run = true;
	stdfd.in = 0;
	stdfd.out = 1;
	stdfd.err = 2;
	set_signal();
	while (gmrs != NULL)
	{
		gmr = (t_gmr *)gmrs->content;
		get_stdfd(&stdfd);
		if (run)
		{
			pipe(pfd);
			if (gmr->exec_env == MAINSHELL)
				exec_simplecmd(gmr->datas, shell);
			else if (gmr->exec_env == SUBSHELL)
				exec_pipeline(gmr->datas, pfd, shell);
		}
		set_stdfd(&stdfd);
		run = check_operator(gmr, shell);
		gmrs = gmrs->next;
	}
}
