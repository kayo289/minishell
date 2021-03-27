#include "../../includes/shell_variable.h"

void set_shell_var(t_shell_var this, char *param)
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
	if ((lst = this->hash_table[h]) == NULL)
		this->hash_table[h] = ft_lstnew(p);
	else
	{
		while (lst != NULL)
		{
			if (ft_strcmp(((t_param*)lst->content)->key, p->key) == 0)
				((t_param*)lst->content)->value = p->value;
			lst = lst->next;
		}
	}
}
