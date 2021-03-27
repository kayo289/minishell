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

static char *pop(t_queue *queue)
{
	t_list *head;

	head = *queue;
	*queue = (*queue)->next;
	return ((char *)head->content);
}

void exec(t_args *args, t_shell_var *sv, t_queue *vars)
{
	pid_t pid;
	int status;
	char *var;

	signal(SIGINT, SIG_IGN);
	set_signal(SIGINT);

	if (***args == NULL)
	{
		var = pop(vars);
		set_shell_var(*sv, var);
	}
	else
	{
		if ((pid = fork()) == 0)
			exec_pipeline(0, *args, fetch_path(args, sv));
		else
		{
			waitpid(pid, &status, 0);
			free(*args);
			*args = ft_calloc3(sizeof(char **), 1);
		}
	}
}

