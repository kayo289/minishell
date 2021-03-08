#include "../includes/minishell.h"

static void sigint(int p_signame);
static void set_signal(int p_signame);

void exe_cmd(int i, char ***args, char **path)
{
	int pp[2]; 
	pid_t pid;

	if (args[i + 1] == NULL)
	{
		execve(path[i], args[i], NULL);
		return;
	}
	pipe(pp);
	pid = fork();
	if (pid == 0)
	{
		// child
		dup2(pp[1], 1);
		close(pp[0]);
		close(pp[1]);

		exe_cmd(i + 1, args, path);
	}
	else if (pid > 0)
	{
		// parent
		close(pp[1]);
		dup2(pp[0], 0);
		close(pp[0]);

		execve(path[i], args[i], NULL);
	}
}

void minish_loop(void)
{
	int run;
	int status;
	char *line;
	pid_t pid;

	run = 1;
	while (run > 0)
	{
		write(1, "minishell$ ", 11);
		set_signal(SIGINT);
		if ((run = get_next_line(0, &line)) == 0)
			break;
		signal(SIGINT, SIG_IGN);
		if ((pid = fork()) == 0)
			parse_line(line);
		else 
			waitpid(pid, &status, 0);
		free(line);
	}
	write(1, "exit\n", 5);
	free(line);
	exit(0);
} 

static void sigint(int p_signame)
{
	p_signame++;
	write(1, "\b\b  ", 4);
	write(1, "\nminishell$ ", 12);
}

static void set_signal(int p_signame)
{
	if (signal(p_signame, sigint) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

int main()
{
	minish_loop();
	return (0);
}
