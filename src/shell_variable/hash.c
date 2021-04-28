#include "../../includes/minishell.h"

int hash(char *name)
{
	int i;
	int h;
	
	h = 0;
	i = 0;
	while (name[i] != '\0')
	{
		h = h * 10 + name[i];
		h %= HASH_SIZE;
		i++;
	}
	return (h);
}
