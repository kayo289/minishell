#include "../../includes/minishell.h"

void set_shell_var(t_shell *this, char *param)
{
	t_list	*lst;
	char	*tmp;
	char	*var;
	char	*name;
	int		h;

	name = get_param_name(param);
	h = hash(name);
	lst = this->var[h];
	while (lst != NULL)
	{
		var = get_param_name(lst->content);
		if (ft_strcmp(var, name) == EQUAL)
		{
			tmp = lst->content;
			lst->content = ft_strdup(param);
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
