#include "../../includes/minishell.h"

int main(int argc, char **argv)
{
	int i = 0;
	char buf[1000]={};

	read(0, buf, 1000);
	printf("call export\n");
	printf("%s\n",buf); 
	while (i < argc){
		printf("argv[%d]: %s\n", i , argv[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
