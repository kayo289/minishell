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

static void lt(char *file, int n)
{
	int fd;

	if ((fd = open(file, O_RDWR)) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	dup2(fd, n);
}

void redirect(t_queue *fds, t_shell *shell)
{
	int		n;
	char	*rdt;
	char	*file;

	while (!q_empty(fds))
	{
		rdt = deq(fds);
		file = deq(fds);
		n = 0;
		while (ft_isalnum(*rdt))
		{
			n = n * 10 + (*rdt++ - '0');
			if (n > 256)
				err_badfd(n, shell);
		}
		if (*rdt == '>')
		{
			if (n == 0)
				n = 1;
			if (*++rdt == '>')
				dgt(file, n);
			else
				gt(file, n);
		}
		else if (*rdt == '<')
			lt(file, n);
	}
}
