#include "../../includes/minishell.h"

static void exec_in_subshell(int i, t_list *datas, int ppfd[], t_shell *shell)
{
	int pfd[2];
	pid_t pid;
	int status;
	char **args;
	t_data *data;

	data = (t_data *)datas->content;
	if (data->args == NULL)
		return;
	args = (char **)data->args->content;
	data->args = data->args->next;

	pipe(pfd);
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(ppfd[0], 0);
		close(ppfd[0]);
		close(ppfd[1]);

		if (data->args != NULL)
			dup2(pfd[1], 1);
		close(pfd[0]);
		close(pfd[1]);

		if (bltin_execute(args, shell) == EXEC)
			exit(0);
		redirect(datas, shell);
		cmds_execute(args, shell);
	}
	exec_in_subshell(i + 1, datas, pfd, shell);
	close(ppfd[0]);
	close(ppfd[1]);
	waitpid(pid, &status, 0);
}

static void exec(t_list *datas, t_shell *shell)
{
	pid_t pid;
	int status;
	char **args;

	args = (char **)((t_data *)datas->content)->args->content;
	if (*args == NULL)
	{
		assign_variable(datas, shell);
		return;
	}

	redirect(datas, shell);
	if (bltin_execute(args, shell) == EXEC)
		return;
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirect(datas, shell);
		cmds_execute(args, shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			(*shell)->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*shell)->exit_status = WTERMSIG(status) + 128;
		free(*args);
	}
}

void interpreter(t_list *datas, t_shell *shell)
{
	int pfd[2];
	int stdin_fd;
	int stdout_fd;
	int stderr_fd;

	stdin_fd = dup(0);
	stdout_fd = dup(1);
	stderr_fd = dup(2);

	set_signal();
	while (datas != NULL)
	{
		if (((t_data *)datas->content)->grammer == SIMPLECMD)
			exec(datas, shell);
		else if (((t_data *)datas->content)->grammer == PIPELINE)
		{
			pipe(pfd);
			exec_in_subshell(0, datas, pfd, shell);
		}
		datas = datas->next;
	}

	dup2(stdin_fd, 0);
	dup2(stdout_fd, 1);
	dup2(stderr_fd, 2);
}
/*
while (((t_data *)datas->content)->args != NULL)
{
for (int i = 0; ((char **)((t_data *)datas->content)->args->content)[i] != NULL; i++)
{
printf("args[%d]:%s\n", i, ((char **)((t_data *)datas->content)->args->content)[i]);
}
((t_data *)datas->content)->args = ((t_data *)datas->content)->args->next;
}
*/
