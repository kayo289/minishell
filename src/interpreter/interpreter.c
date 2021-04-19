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

static void set_signal(void)
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

void exec_in_subshell(args, fds, ppfd, shell)
	t_args args; t_queue *fds; int **ppfd; t_shell *shell;
{
	pid_t pid;
	int pfd[2];

	if (**args == NULL)
		return;
	set_signal();
	pipe(pfd);
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2((*ppfd)[0], 0);
		close((*ppfd)[0]);
		close((*ppfd)[1]);

		dup2(pfd[1], 1);
		close(pfd[0]);
		close(pfd[1]);

		if (builtin_execute(args, shell))
			exit(0);
		redirect(fds);
		command_execute(args, shell);
	}
	else
	{
		close((*ppfd)[0]);
		close((*ppfd)[1]);
		(*ppfd)[0] = pfd[0];
		(*ppfd)[1] = pfd[1];
		free(*args);
	}
}


void exec(args, fds, ppfd, shell)
	t_args args; t_queue *fds; int **ppfd; t_shell *shell;
{
	pid_t pid;
	//int status;

	if (**args == NULL)
		return;
	set_signal();
	if (builtin_execute(args, shell))
		return;
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2((*ppfd)[0], 0);
		close((*ppfd)[0]);
		close((*ppfd)[1]);
		redirect(fds);
		command_execute(args, shell);
	}
	else
	{
		wait(NULL);
		close((*ppfd)[0]);
		close((*ppfd)[1]);
		free(*args);
	}
}
