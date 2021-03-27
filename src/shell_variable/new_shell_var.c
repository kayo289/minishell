#include "../../includes/shell_variable.h"

t_shell_var new_shell_var(void)
{
	extern char **environ;
	t_shell_var this;
	int i;

	this = malloc(sizeof(t_shell_var));
	i = -1;
	while (++i < HASH_SIZE)
	{
		this->hash_table[i] = malloc(sizeof(t_list)); 
		this->hash_table[i] = NULL;
	}
	i = -1;
	while (environ[++i] != NULL)
		set_shell_var(this, environ[i]);
	set_shell_var(this, "PATH=./cmds");
	return (this);
}

