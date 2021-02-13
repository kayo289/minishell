#include "../includes/minishell.h"

void lsh_loop()
{
	int status;
	char *line;
	char **args;

	status = 1;
	while (status)
	{
		write(1, ">", 1);
		status = get_next_line(0, &line);
	}
}

int main()
{
	lsh_loop();
	return (0);
}
