#include "../../includes/minishell.h"

void set_shell_var(t_shell *this, char *param)
{
	t_list	*lst;
	char	*tmp;
	char	*var;
	char	*name;
	char	*new_param;
	int		h;

	name = get_param_name(param);
	h = hash(name);
	lst = this->var[h];
	while (lst != NULL)
	{
		var = get_param_name(lst->content);
		if (ft_strcmp(var, name) == EQUAL)
		{
			if (ft_strnstr(param, "+=", ft_strlen(param)) != NULL)
			{
				new_param = ft_strjoin(get_param_value(lst->content), get_param_value(param));
				new_param = ft_strjoin("=", new_param);
				new_param = ft_strjoin(name, new_param);
			}
			else
				new_param = ft_strdup(param);
			tmp = lst->content;
			lst->content = new_param;
			set_environ(this, name);
			free(tmp);
			free(name);
			free(var);
			return;
		}
		free(var);
		lst = lst->next;
	}
	free(name);
	ft_lstadd_back(&this->var[h], ft_lstnew(ft_strdup(param)));
	return;
}
