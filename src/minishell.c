#include "../includes/minishell.h"

const char *cmds[] = {
	"./cd",
	"./echo",
	"./env", 
	"./exit", 
	"./export",
	"./pwd",
	"./unset",
	NULL
};

/*
void (*builtin_func[]) () = {
  	minish_cd,
	minish_echo,
  	minish_env,
  	minish_exit,
	minish_export,
	minish_pwd,
	minish_unset
};
*/

int parse_command(char *cmd)
{
	int n;

	n = 0;
	while (cmds[n] != NULL)
	{
		if (ft_strncmp(cmd, cmds[n], ft_strlen(cmds[n])) == 0) 
			break;
		n++;
	}
	return (n);
}

int execute(char *cmd)
{
	int cmd_no;
	int status;
	pid_t pid;
	//char *arg[];

	pid = fork();
	if (pid < 0)
		printf("Error:%s\n", strerror(errno));
	else if (pid == 0)
	{
		// child
		cmd_no = parse_command(cmd);
		//if (cmds[cmd_no] != NULL)
			//execve(cmds[cmd_no], arg, NULL);
		exit(0);
	}	
	// parent
	if (waitpid(pid, &status, 0) < 0)
	{
		printf("Error:%s\n", strerror(errno));
		exit(0);
	}
	//printf("exit_code: %d\n", WEXITSTATUS(status));
	return (1);
	//if (!WIFEXITED(status))
	//	return (0);
}

int lsh_loop()
{
	int p_status;
	int run;
	char *cmd;
	pid_t pid;

	run = 1;
	while (run != 0)
	{
		write(1, "$", 1);
		run = get_next_line(0, &cmd);
		pid = fork();
		if (pid < 0)
			printf("Error:%s\n", strerror(errno));
		else if (pid == 0)
			// child
			return (execute(cmd));
		// parent
		if (waitpid(pid, &p_status, 0) < 0)
		{
			printf("Error:%s\n", strerror(errno));
			exit(-1);
		}
		if (WIFSTOPPED(p_status))
		free(cmd);
	}
	return (0);
}

int main()
{
	lsh_loop();
	return (0);
}
