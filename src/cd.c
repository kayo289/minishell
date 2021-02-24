#include "../includes/minishell.h"

int main(int argc, char **argv)
{
	int i = 0;

	printf("call cd\n");
	while (i < argc){
		printf("argv[%d]: %s\n", i , argv[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
