#include "../includes/minishell.h"

#define MESSAGE ": command not found"

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

void exec_cmd(int i, char ***args, char **path)
{
	int pp[2]; 
	pid_t pid;

	if (args[i + 1] == NULL)
	{
		execve(path[i], args[i], NULL);
		error(args[i][0], MESSAGE);
	}
	pipe(pp);
	pid = fork();
	if (pid == 0)
	{
		// child
		dup2(pp[1], 1);
		close(pp[0]);
		close(pp[1]);

		exec_cmd(i + 1, args, path);
	}
	else if (pid > 0)
	{
		// parent
		close(pp[1]);
		dup2(pp[0], 0);
		close(pp[0]);

		execve(path[i], args[i], NULL);
		error(args[i][0], MESSAGE);
	}
}

void minish_loop(void)
{
	char *line;

	while (1)
	{
		write(1, "minishell$ ", 11);
		set_signal(SIGINT);
		if (get_next_line(0, &line) == 0)
		{
			write(1, "exit\n", 5);
			free(line);
			exit(0);
		}
		parse_line(line);
		free(line);
	}
} 

int main(void)
{
	minish_loop();
	return (0);
}
