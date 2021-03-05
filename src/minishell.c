#include "../includes/minishell.h"

void exe_cmd(int i, char ***args, char **path)
{
	int pp[2];
	pid_t pid;

	if (args[i + 1] == NULL)
	{
		printf("args[%d]:%s\n", i, args[i][0]);
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

		printf("args[%d]:%s\n", i, args[i][0]);
		execve(path[i], args[i], NULL);
	}
}

int minish_loop(void)
{
	int run;
	char *line;

	run = 1;
	while (run != 0)
	{
		write(1, ">", 1);
		run = get_next_line(0, &line);
		if (fork() == 0)
			parse_line(line);
		else 
			wait(NULL);
		free(line);
	}
	return (0);
}

void sig_handler(int p_signame)
{
	write(1, "\n>", 2);
	set_signal(p_signame);
	return;
}

void set_signal(int p_signame)
{
	if (signal(p_signame, sig_handler) == SIG_ERR){
		printf("cannot catch signal");
		exit(1);
	}
}

int main()
{
	set_signal(SIGINT);
	minish_loop();
	return (0);
}
