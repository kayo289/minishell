#include "../../includes/minishell.h"

static void assign_variable(t_queue vars, t_shell *shell)
{
	char *var;

	while (!q_empty(&vars))
	{
		var = deq(&vars);
		set_shell_var(*shell, var);
	}
}

static void exec_pipeline(t_list *datas, int ppfd[], t_shell *shell)
{
	int pfd[2];
	pid_t pid;
	int status;
	int n;
	t_data *data;

	if (datas == NULL)
		return;
	data = (t_data *)datas->content;
	pipe(pfd);
	pid = fork();
	if (pid < 0)	
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	else if (pid == 0)
	{
		n = 0;
		if (data->args[0] == NULL)
			assign_variable(data->vars, shell);
		else
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(ppfd[0], 0);
			close(ppfd[0]);
			close(ppfd[1]);

			if (datas->next != NULL)
				dup2(pfd[1], 1);
			close(pfd[0]);
			close(pfd[1]);

			redirect(data->fds, shell);
			if (lookup_bltin(data->args))
				n = bltin_execute(data->args, shell);
			else
				cmds_execute(data->args, shell);
		}
		exit(n);
	}
	exec_pipeline(datas->next, pfd, shell);
	close(ppfd[0]);
	close(ppfd[1]);
	waitpid(pid, &status, 0);
	if (datas->next == NULL)
	{
		if (WIFEXITED(status))
			(*shell)->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*shell)->exit_status = WTERMSIG(status) + 128;
	}
}

static void exec_simplecmd(t_list *datas, t_shell *shell)
{
	pid_t	pid;
	int		status;
	t_data	*data;

	data = datas->content;
	if (data->args[0] == NULL)
	{
		assign_variable(data->vars, shell);
		return;
	}
	redirect(data->fds, shell);
	if (lookup_bltin(data->args))
		bltin_execute(data->args, shell);
	else
	{
		pid = fork();
		if (pid < 0)	
		{
			ft_putendl_fd(strerror(errno), 2);
			exit(1);
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			cmds_execute(data->args, shell);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				(*shell)->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				(*shell)->exit_status = WTERMSIG(status) + 128;
			free(data->args);
		}
	}
}

void interpreter(t_list *gmrs, t_shell *shell)
{
	int pfd[2];
	int stdin_fd;
	int stdout_fd;
	int stderr_fd;
	t_grammer *gmr;

	set_signal();
	while (gmrs != NULL)
	{
		stdin_fd = dup(0);
		stdout_fd = dup(1);
		stderr_fd = dup(2);
		pipe(pfd);
		gmr = (t_grammer *)gmrs->content;
		if (gmr->name == SIMPLECMD)
			exec_simplecmd(gmr->datas, shell);
		else if (gmr->name == PIPELINE)
			exec_pipeline(gmr->datas, pfd, shell);
		dup2(stdin_fd, 0);
		dup2(stdout_fd, 1);
		dup2(stderr_fd, 2);
		gmrs = gmrs->next;
	}
}
