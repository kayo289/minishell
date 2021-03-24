#include "../../includes/minishell.h"


static void check_flag(char *argv, t_echo_flag *f){
	int i;
	int n;
	int another;

	i = 0;
	n = 0;
	another = 0;
	//printf("%s\n",argv);
	if (argv[i++] != '-')
		return;
	while(argv[i] != '\0')
	{
		if (argv[i] == 'n')
			n = 1;
		else
			another = 1;
		i++;
	}
	//printf("n:%d,another:%d\n",n,another);
	if (another == 1)
		f->another = 1;
	if (n == 1 && another == 0)
		f->n = 1;
}
static void output(int pos, int argc, char **argv, t_echo_flag *f)
{
	if (pos + 1 >= argc)
	{
		check_flag(argv[pos], f);
		if ((argv[pos][0] == '-' && f->another == 1) || argv[pos][0] != '-')
			ft_putstr_fd(argv[pos], 1);
		return;
	}
	check_flag(argv[pos], f);
	if ((argv[pos][0] == '-' && f->another == 1) || argv[pos][0] != '-')
	{
		ft_putstr_fd(argv[pos], 1);
		ft_putstr_fd(" ", 1);
	}
	output(pos + 1, argc, argv, f);
}

static void init_flag(t_echo_flag *f)
{
	f->n = 0;
	f->another = 0;
}

int main(int argc, char **argv)
{
	t_echo_flag f;

	init_flag(&f);
	if (argc <= 1)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	output(1, argc, argv, &f);
	if (f.n == 0)
		ft_putstr_fd("\n", 1);
	exit(0);
}
