#include "../../includes/minishell.h"

#define MESSAGE ": command not found"

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

static void exec_pipeline(int i, char ***args, char **path)
{
	int pp[2];
	pid_t pid;

	if (args[i + 1] == NULL)
	{
		execve(path[i], args[i], NULL);
		error(args[i][0], MESSAGE);
	}
	pipe(pp);
	pid = fork();
	if (pid == 0)
	{
		// child
		dup2(pp[1], 1);
		close(pp[0]);
		close(pp[1]);

		exec_pipeline(i + 1, args, path);
	}
	else if (pid > 0)
	{
		// parent
		close(pp[1]);
		dup2(pp[0], 0);
		close(pp[0]);

		execve(path[i], args[i], NULL);
		error(args[i][0], MESSAGE);
	}
}

void go_exec_pipeline(char ****args, t_shell_var sv)
{
	pid_t pid;
	int status;

	signal(SIGINT, SIG_IGN);
	set_signal(SIGINT);
	if ((pid = fork()) == 0)
		exec_pipeline(0, *args, fetch_path(args, sv));
	else
	{
		waitpid(pid, &status, 0);
		//free(*args);
	}
}

