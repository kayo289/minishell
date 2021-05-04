#include "../includes/minishell.h"

static void minishell_loop(t_shell *shell)
{
	t_dlist *line;
	t_list	*tokens;

	while (1)
	{
		prompt("minishell$ ", &line, shell);
		lexer(line, &tokens, shell);
		parser(tokens, shell);
		ft_dlstclear(&line, free);
		ft_lstclear(&tokens, ip_free);
	}
}

void minishell_end(t_shell *shell)
{
	int i;

	i = 0;
	while (i < HASH_SIZE)
	{
		ft_lstclear(&shell->var[i], param_free);
		i++;
	}
	shell->hist_lst = ft_dlsttop(shell->hist_lst);
	ft_dlstclear(&shell->hist_lst, free);
	free(shell->histfile_path);
	exit(shell->exit_status);
}

int main(void)
{
	t_shell shell;

	new_shell_var(&shell);
	minishell_loop(&shell);
	minishell_end(&shell);
	return (0);
}
