#include "../../includes/shell_var.h"

int hash(char *name)
{
	int i;
	int h;
	
	h = 0;
	i = 0;
	while (name[i] != '\0')
	{
		h = h * 10 + name[i];
		h %= SIZE;
		i++;
	}
	return (h);
}
