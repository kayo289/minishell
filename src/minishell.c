#include "../includes/minishell.h"

static void minishell_loop(t_shell *shell)
{
	t_dlist *line;
	t_list	*tokens;

	while (1)
	{
		prompt("minishell$ ", &line, shell);
		lexer(&line, &tokens, shell);
		parser(tokens, shell);
		while (wait(NULL) > 0);
		ft_lstclear(&tokens, free);
	}
} 

int main(void)
{
	t_shell shell;

	shell = new_shell_var();
	minishell_loop(&shell);
	return (0);
}
