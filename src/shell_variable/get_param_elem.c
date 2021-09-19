#include "../../includes/minishell.h"

char *get_param_name(char *param)
{
	char *append_var;
	char *var;

	append_var = ft_strnstr(param, "+=", ft_strlen(param));
	if (append_var == NULL)
	{
		var = ft_strchr(param, '=');
		if (var == NULL)
			return (ft_strdup(param));
		return (ft_substr(param, 0, var - param));
	}
	return (ft_substr(param, 0, append_var - param));
}

char *get_param_value(char *param)
{
	char *val;

	val = ft_strchr(param, '=');
	if (val == NULL)
		return NULL;
	return (ft_strdup(val + 1));
}
