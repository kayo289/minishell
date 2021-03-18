#include "../includes/minishell.h"

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

static void primary_prompt(t_shell_var sv)
{
	char *line;
	t_queue tokens;

	while (1)
	{
		//ft_putstr_fd(get_shell_var(sv, "PS1"), 1);
		ft_putstr_fd("minishell$ ", 1);
		set_signal(SIGINT);
		if (get_next_line(0, &line) == 0)
		{
			write(1, "exit\n", 5);
			free(line);
			exit(0);
		}
		lexer(line, &tokens, sv);
		parser(&tokens, sv);
		free(line);
	}
} 

int main(void)
{
	t_shell_var sv;

	sv = new_shell_var();
	primary_prompt(sv);
	return (0);
}
