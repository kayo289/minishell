#include "../includes/minishell.h"

void sigint(int p_signame);
void set_signal(int p_signame);

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

int minish_loop(void)
{
	int run;
	int status;
	char *line;
	pid_t pid;

	run = 1;
	while (run != 0)
	{
		signal(SIGINT, SIG_IGN);
		write(1, "minishell$ ", 11);
		if ((pid = fork()) == 0)
		{
			set_signal(SIGINT);
			run = get_next_line(0, &line);
			parse_line(line);
			free(line);
		}
		else 
			waitpid(pid, &status, 0);
	}
	return (0);
} 

void set_signal(int p_signame)
{
	if (signal(p_signame, sigint) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}

void sigint(int p_signame)
{
	write(1, "\n", 1);
	exit(128 + p_signame);
}

int main()
{
	minish_loop();
	return (0);
}
