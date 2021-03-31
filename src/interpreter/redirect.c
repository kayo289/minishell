#include "../../includes/minishell.h"

static void gt(char *file, int n)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT, S_IWRITE | S_IREAD);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
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
		exit(1);
	}
	dup2(fd, n);
}

static void lt(char *file)
{
	int fd;

	if ((fd = open(file, O_RDWR)) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	fprintf(stderr, "fd:%d\n", fd);
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
		n = 0;
		while (ft_isalnum(*rdct))
			n = n * 10 + (*rdct++ - '0');
		file = pop(fds);
		if (*rdct == '>')
		{
			if (n > 256)
				err_badfd(n);
			if (n != 2)
				n = 1;
			if (*++rdct == '>')
				dgt(file, n);
			else
				gt(file, n);
		}
		else if (*rdct == '<')
			lt(file);
	}
}
