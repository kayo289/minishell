#include "../../includes/minishell.h"

static void gt(char *file, int n)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT, S_IWRITE | S_IREAD);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return;
	}
	dup2(fd, n);
}

static void dgt(char *file, int n)
{
	int fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE | S_IREAD);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return;
	}
	dup2(fd, n);
}

static void lt(char *file)
{
	int fd;

	if ((fd = open(file, O_RDWR)) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return;
	}
	dup2(fd, 0);
}

void redirect(t_queue *fds)
{
	int		n;
	char	*rdct;
	char	*file;

	while (*fds != NULL)
	{
		rdct = pop(fds);
		n = ft_atoi(rdct);
		file = pop(fds);
		if (ft_strnstr(rdct, ">>", 2) == 0)
		{
			if (n != 2)
				n = 1;
			else if (n > 256)
				err_badfd(n);
			gt(file, n);
		}
		else if (ft_strnstr(rdct, ">", 1) == 0)
		{
			if (n != 2)
				n = 1;
			else if (n > 256)
				err_badfd(n);
			dgt(file, n);
		}
		else if (ft_strnstr(rdct, "<", 1) == 0)
			lt(file);
	}
}
