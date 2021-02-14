#include "../includes/minishell.h"

const char *cmds[] = {
	"cd",
	"env", 
	"exit", 
	"export",
	"pwd",
	"unset",
	NULL
};

void (*builtin_func[]) () = {
  	minish_cd,
  	minish_env,
  	minish_exit,
	minish_export,
	minish_pwd,
	minish_unset
};

int parse_cmd(char *cmd)
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
	int pid;

	cmd_no = parse_cmd(cmd);
	if (cmds[cmd_no] == NULL)
		return 0;
	(*builtin_func[cmd_no])();
	return 1;
}

void lsh_loop()
{
	int status;
	char *cmd;

	status = 1;
	while (status)
	{
		write(1, ">", 1);
		get_next_line(0, &cmd);
		execute(cmd);
		sleep(1);
		free(cmd);
	}
}

int main()
{
	lsh_loop();
	return (0);
}
