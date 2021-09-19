#include "../../includes/minishell.h"

char *get_param_name(char *param)
{
	char *val;

	val = ft_strnstr(param, "+=", ft_strlen(param));
	if (val == NULL)
		return (ft_substr(param, 0, ft_strchr(param, '=') - param));
	else
		return (ft_substr(param, 0, val - param));
}

char *get_param_value(char *param)
{
	return (ft_strdup(ft_strchr(param, '=') + 1));
}
