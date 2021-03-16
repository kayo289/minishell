#include "../includes/minishell.h"

int find_except_c(char *argv, char c)
{
	int		i;

	i = 0;
	if (c == '\0')
		return (1);
	while (argv[i] != '\0')
	{
		if (argv[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	int i;
	int n_opt;

	i = 0;
	n_opt = 0;
	while (++i < argc){
		if (argv[i][0] == '-')
		{
			if (find_except_c(&argv[i][1], 'n') == 0)
			{
				n_opt = 1;
				continue;
			}
		}
		ft_putstr_fd(argv[i], 1);
	}
	if (n_opt == 0)
		ft_putstr_fd("\n", 1);
	exit(0);
}
