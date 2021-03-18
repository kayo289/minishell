#include "../../includes/shell_variable.h"

t_shell_var new_shell_var(void)
{
	int	fd;
	char *line;
	t_shell_var this;
	int i;

	this = malloc(sizeof(t_shell_var));
	i = 0;
	while (i < HASH_SIZE)
	{
		this->hash_table[i] = malloc(sizeof(t_list)); 
		this->hash_table[i] = NULL;
		i++;
	}
	// dummy
	return (this);
	fd = open(".minishellrc", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line:%s\n", line);
		//parse_line(line, this);
	}
	return (this);
}

