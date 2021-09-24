#include "../../includes/minishell.h"

static void execute_extern_cmd(char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)	
	{
		ft_putendl_fd(strerror(errno), 2);
		shell->exit_status = 1;
		return;
	}
	else if (pid == 0)
	{
		set_signal_dfl();
		execute_cmds(args, shell);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = WTERMSIG(status) + 128;
	}
}

void exec_simplecmd(t_list *datas, t_shell *shell)
{
	t_data	*data;
	char	**args;

	data = datas->content;
	if (data->words == NULL)
	{
		assign_variable(&data->vars, shell);
		return;
	}
	args = expand_words(data->words, shell, true);
	if (redirect(&data->fds, shell) == FAIL)
		return;
	if (lookup_bltin(args))
		execute_bltin(args, shell);
	else
		execute_extern_cmd(args, shell);
	dp_free(args);
}

