#include "../../includes/minishell.h"

/*
static void exec_in_subshell(t_list *datas, int **ppfd, t_shell *shell)
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

		if (bltin_execute(args, shell) == EXEC)
			exit(0);
		redirect(((t_data*)datas->content)->fds, shell);
		cmd_execute(args, shell);
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
*/
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
	if (bltin_execute(args, shell) == EXEC)
		return;
	set_signal();
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirect(datas, shell);
		cmd_execute(args, shell);
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
	while (datas != NULL)
	{
		if (((t_data *)datas->content)->grammer == SIMPLECMD)
			exec(datas, shell);
		else if (((t_data *)datas->content)->grammer == PIPELINE)
			return;
			//exec_in_subshell(datas, ppfd, shell);
		datas = datas->next;
	}
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
