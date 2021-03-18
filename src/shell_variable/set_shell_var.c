#include "../../includes/shell_variable.h"

void set_shell_var(t_shell_var this, char *param)
{
	t_map *map;
	t_list *new;
	char **str;
	int h;
	int i;

	str = ft_split(param, '=');
	map = malloc(sizeof(t_map));
	map->key = str[0];
	map->value = ft_strdup("");
	i = 1;
	while (str[i] != NULL)
		map->value = ft_strjoin(map->value, str[i++]);
	h = hash(str[0]);
	new = ft_lstnew(map);
	ft_lstadd_back(&(this->hash_table[h]), new);
}
