#include "../../includes/minishell.h"

static void exec_pipeline_child(t_list *datas, int pfd[], int ppfd[], t_shell *shell)
{
	t_data *data;
	char	**args;

	data = (t_data *)datas->content;
	if (data->words == NULL)
		assign_variable(&data->vars, shell);
	else
	{
		set_signal_dfl();
		dup2(ppfd[0], 0);
		close(ppfd[0]);
		close(ppfd[1]);

		if (datas->next != NULL)
			dup2(pfd[1], 1);
		close(pfd[0]);
		close(pfd[1]);

		args = expand_words(data->words, shell, true);
		if (redirect(&data->fds, shell) == FAIL)
			exit(shell->exit_status);
		if (lookup_bltin(args))
			execute_bltin(args, shell);
		else
			execute_cmds(args, shell);
	}
	minishell_end(shell);
}


void exec_pipeline(t_list *datas, int ppfd[], t_shell *shell)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	if (datas == NULL)
		return;
	pipe(pfd);
	pid = fork();
	if (pid < 0)	
	{
		ft_putendl_fd(strerror(errno), 2);
		shell->exit_status = 1;
		return;
	}
	else if (pid == 0)
		exec_pipeline_child(datas, pfd, ppfd, shell);
	close(ppfd[0]);
	close(ppfd[1]);
	exec_pipeline(datas->next, pfd, shell);
	waitpid(pid, &status, 0);
	if (datas->next == NULL)
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = WTERMSIG(status) + 128;
	}
}

