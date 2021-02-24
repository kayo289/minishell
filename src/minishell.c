#include "../includes/minishell.h"

int argc = 0;
void do_cmd(int i, char ***args)
{
	int pp[2];
	pid_t pid;

	if (i >= argc - 1)
		execve(args[0][0], args[0], NULL);
	else
	{
		pipe(pp);
		pid = fork();
		if (pid == 0)
		{
			// child
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);

			do_cmd(i + 1, args);
		}
		else if (pid > 0)
		{
			// parent
			close(pp[1]);
			dup2(pp[0], 0);
			close(pp[0]);

			execve(args[argc - i - 1][0], args[argc - i - 1], NULL);
		}
	}
}

char ***split_line(char *line)
{
	char ***args;
	int i;

	line++;
	// default
	argc = 2;
	args = (char ***)malloc(sizeof(char **) * argc);
	for (i = 0; i < argc; i++)
		args[i] = (char **)malloc(sizeof(char *) * 4);
	args[1][0] = "export";
	args[1][1] = "hello";
	args[1][2] = "Hello";
	args[1][3] = NULL;
	args[0][0] = "echo";
	args[0][1] = "$hello";
	args[0][2] = NULL;
	return (args);

	/*
	* asignees kkikuchi
	* ex)
	*	line = echo "Hello World" 
	*		args[0][0] = "echo"
	*		args[0][1] = "Hello World"
	*		args[0][2] = NULL
	*
	*	line = echo "Hello World" >> output.txt
	*		args[0][0] = "echo"
	*		args[0][1] = "Hello World"
	*		args[0][2] = NULL
	*		args[1][0] = text.txt 
	*		args[1][1] = NULL
	*
	*	line = export hello="Hello"; echo $hello
	*		args[0][0] = "export"
	*		args[0][1] = hello
	*		args[0][2] = "Hello"
	*		args[0][3] = NULL
	*		args[1][0] = echo
	*		args[1][1] = $hello
	*		args[1][2] = NULL
	*	
	*	line = export hello="Hello"; echo $hello >> output.txt
	*		args[0][0] = "export"
	*		args[0][1] = hello
	*		args[0][2] = "Hello"
	*		args[0][3] = NULL
	*		args[1][0] = echo
	*		args[1][1] = $hello
	*		args[1][2] = NULL
	*		args[2][0] = output.txt
	*		args[2][1] = NULL
	*
	*	line = exit ;pwd
	*		args[0][0] = "export"
	*		args[0][1] = hello
	*		args[0][2] = "Hello"
	*		args[0][3] = NULL
	*		args[1][0] = echo
	*		args[1][1] = $hello
	*		args[1][2] = NULL
	*		args[2][0] = output.txt
	*		args[2][1] = NULL
	*/
}

int minish_loop(void)
{
	int run;
	char *line;
	char ***args;

	run = 1;
	while (run != 0)
	{
		write(1, ">", 1);
		run = get_next_line(0, &line);
		args = split_line(line);
		if (fork() == 0)
			do_cmd(0, args);
		else 
			wait(NULL);
		free(line);
	}
	return (0);
}

int main()
{
	minish_loop();
	return (0);
}
