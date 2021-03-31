#include "../includes/minishell.h"

static void minishell_loop(t_shell_var *sv)
{
	t_dlist *line;
	t_queue tokens;

	while (1)
	{
		prompt("minishell$ ", &line);
		lexer(&line, &tokens, sv);
		parser(&tokens, sv);
		while (wait(NULL) > 0);
		//ft_dlstclear(line);
	}
} 

int main(void)
{
	t_shell_var sv;

	sv = new_shell_var();
	minishell_loop(&sv);
	return (0);
}
