#include "../../includes/minishell.h"

static t_param *create_param(char *param)
{
	t_param *p;
	char **str;
	char *tmp;
	int i;

	str = ft_split(param, '=');
	p = (t_param *)malloc(sizeof(t_param));
	p->key = ft_strdup(str[0]);
	p->value = ft_strdup("");
	i = 1;
	while (str[i] != NULL)
	{
		tmp = p->value;
		p->value = ft_strjoin(p->value, str[i++]);
		free(tmp);
	}
	
	i = 0; 
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
	return (p);
}

void set_shell_var(t_shell *this, char *param)
{
	t_param *p;
	t_list *lst;
	int h;

	p = create_param(param);
	h = hash(p->key);
	lst = this->var[h];
	while (lst != NULL)
	{
		if (ft_strcmp(((t_param *)lst->content)->key, p->key) == EQUAL)
		{
			((t_param*)lst->content)->value = p->value;
			return;
		}
		lst = lst->next;
	}
	ft_lstadd_back(&this->var[h], ft_lstnew(p));
}
