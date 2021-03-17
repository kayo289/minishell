#include "../includes/minishell.h"

int			ft_strchr_n(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

int ft_getopt(char *argv,char *target)
{
	static int i;

	if (i < ft_strlen(argv))
	{
		i++;
		if (argv[i]!=0)
			return (ft_strchr_n(target, argv[i]));
	}
	return (-2);
}

void init_opts(int *opt, int n)
{
	int i;

	i = 0;
	while (i < n)
		opt[i++] = 0;
}

int main(int argc, char **argv)
{
	int i;
	int opt_i;
	int opts[2];
	int cnt;

	i = 0;
	opt_i = 0;
	cnt = 0;
	init_opts(opts, 2);
	while (++i < argc){
		if (argv[i][0] == '-' && ft_strlen(argv[i]) != 1 )
		{
			while ((opt_i = ft_getopt(&argv[i][0], "n")) != -2)
			{
				printf("opt_i:%d\n",opt_i);
				opts[opt_i + 1] = 1;
			}
			if (opts[1] == 1)
				continue;
		}
		cnt++;
		if (cnt != 1)
			ft_putstr_fd(ft_strjoin(" ", argv[i]), 1);
		else
			ft_putstr_fd(argv[i], 1);
	}
	if (opts[i] == 0)
		ft_putstr_fd("\n", 1);
	exit(0);
}
