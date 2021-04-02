#include "../../includes/minishell.h"

int builtin_execute(t_args args)
{
	int			i;
	const char	*builtin_str[] = {"cd", "echo", "pwd", NULL};
	void (*builtin_func[])(char **) = {cd, echo, pwd};

	i = 0;
	while (builtin_str[i] != NULL)
	{
		if (ft_strcmp((*args)[0], builtin_str[i]) == 0)
		{
			(*builtin_func[i])(*args);
			return(1);
		}
		i++;
	}
	return(0);
}
