#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i;

	i = 1;
	printf("getenv:%s\n",getenv(argv[i]));
	if (argc <= 1)
		return (0);
	while (argv[i] != NULL)
	{
		printf("argv:%s\n",argv[i]);
		ft_unsetenv(argv[i]);
		i++;
	}
	return (0);
}
