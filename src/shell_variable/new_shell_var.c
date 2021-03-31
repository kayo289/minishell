#include "../../includes/minishell.h"

t_shell new_shell_var(void)
{
	extern char	**environ;
	t_shell		this;
	int			i;

	this = malloc(sizeof(t_shell));
	i = -1;
	while (++i < SIZE)
	{
		this->var[i] = malloc(sizeof(t_list)); 
		this->var[i] = NULL;
	}
	i = -1;
	while (environ[++i] != NULL)
		set_shell_var(this, environ[i]);
	return (this);
}
