#include "../../includes/minishell.h"

void set_shell_var(t_shell this, char *param)
{
	t_param *p;
	t_list *lst;
	char **str;
	int h;
	int i;

	str = ft_split(param, '=');
	p = malloc(sizeof(t_param));
	p->key = str[0];
	p->value = ft_strdup("");
	i = 1;
	while (str[i] != NULL)
		p->value = ft_strjoin(p->value, str[i++]);
	h = hash(p->key);
	lst = this->var[h];
	while (lst != NULL)
	{
		if (ft_strcmp(((t_param*)lst->content)->key, p->key) == EQUAL)
		{
			((t_param*)lst->content)->value = p->value;
			return;
		}
		lst = lst->next;
	}
	ft_lstadd_back(&this->var[h], ft_lstnew(p));
}
