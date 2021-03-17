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

static void primary_prompt(char ***shell_var)
{
	char *line;

	while (1)
	{
		ft_putstr_fd(get_shell_var("PS1", shell_var), 1);
		set_signal(SIGINT);
		if (get_next_line(0, &line) == 0)
		{
			write(1, "exit\n", 5);
			free(line);
			exit(0);
		}
		parse_line(line, shell_var);
		free(line);
	}
} 

static void boot_minishell(char ***shell_var)
{
	int	fd;
	char *line;

	fd = open(".minishellrc", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		*shell_var = ft_realloc2(*shell_var, line);
}

int main(void)
{
	char **shell_var;

	shell_var = ft_calloc2(sizeof(char*), 1);
	boot_minishell(&shell_var);
	primary_prompt(&shell_var);
	return (0);
}
