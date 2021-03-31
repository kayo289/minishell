#include "../includes/minishell.h"

/*
static void sigint(int p_signame)
{
	p_signame++;
	write(1, "\b\b  \n", 5);
	write(1, "minishell$ ", 11);
}

static void set_signal(int p_signame)
{
	if (signal(p_signame, sigint) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}
*/
static void minishell_loop(t_shell_var *sv)
{
	t_dlist *line;
	t_queue tokens;

	while (1)
	{
		prompt("minishell$ ", &line);
		lexer(&line, &tokens, sv);
		parser(&tokens, sv);
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
