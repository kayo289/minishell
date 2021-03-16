#include "../includes/minishell.h"

int find_except_c(char *argv, char c)
{
	int		i;

	i = 0;
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
	char *str;

	i = 0;
	n_opt = 0;
	while (++i < argc){
		if (argv[i][0] == '-' && ft_strlen(argv[i]) != 1 )
		{
			if (find_except_c(&argv[i][1], 'n') == 0)
			{
				n_opt = 1;
				continue;
			}
		}
		if (argc != 2 && i != 1)
			ft_putstr_fd(ft_strjoin(" ", argv[i]), 1);
		else
			ft_putstr_fd(argv[i], 1);
	}
	if (n_opt == 0)
		ft_putstr_fd("\n", 1);
	exit(0);
}
