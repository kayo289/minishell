#include "../../includes/minishell.h"

char *get_param_name(char *param)
{
	return (ft_substr(param, 0, ft_strchr(param, '=') - param));
}

char *get_param_value(char *param)
{
	return (ft_strdup(ft_strchr(param, '=') + 1));
}
