#include "../../includes/minishell.h"

static void sigint(int p_signame)
{
	write(1, "\b\b  \n", 5);
	exit(p_signame + 128);
}

static void set_signal(int p_signame)
{
	if (signal(p_signame, sigint) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

void exec_a(args, fds, ppfd, sv)
	t_args args; t_queue *fds; int **ppfd; t_shell_var *sv;
{
	pid_t pid;
	int pfd[2];

	signal(SIGINT, SIG_IGN);
	set_signal(SIGINT);
	pipe(pfd);
	if ((pid = fork()) == 0)
	{
		dup2((*ppfd)[0], 0);
		close((*ppfd)[0]);
		close((*ppfd)[1]);

		dup2(pfd[1], 1);
		close(pfd[0]);
		close(pfd[1]);

		redirect(fds);
		execve(fetch_path(args, sv), *args, NULL);
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


void exec_b(args, fds, ppfd, sv)
	t_args args; t_queue *fds; int **ppfd; t_shell_var *sv;
{
	pid_t pid;
	//int status;

	signal(SIGINT, SIG_IGN);
	set_signal(SIGINT);
	if ((pid = fork()) == 0)
	{
		dup2((*ppfd)[0], 0);
		close((*ppfd)[0]);
		close((*ppfd)[1]);
		redirect(fds);
		execve(fetch_path(args, sv), *args, NULL);
	}
	else
	{
		wait(NULL);
		close((*ppfd)[0]);
		close((*ppfd)[1]);
		free(*args);
	}
}

