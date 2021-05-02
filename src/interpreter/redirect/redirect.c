#include "../../../includes/minishell.h"

static void gt(char *file, int n)
{
	int fd;

	if (n == INIT)
		n = STDOUT_FILENO;
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

	if (n == INIT)
		n = STDOUT_FILENO;
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

	if (n == INIT)
		n = STDIN_FILENO;
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
		n = INIT;
		if (ft_isalnum(*rdt))
		{
			n = 0;
			while (ft_isalnum(*rdt))
			{
				n = n * 10 + (*rdt++ - '0');
				if (n > 256)
					err_badfd(n, shell);
			}
		}
		if (ft_strcmp(rdt, ">>") == EQUAL)
			dgt(file, n);
		else if (ft_strcmp(rdt, ">") == EQUAL)
			gt(file, n);
		else if (ft_strcmp(rdt, "<<") == EQUAL)
			here_documents(file, shell);
		else if (ft_strcmp(rdt, "<") == EQUAL)
			lt(file, n);
	}
}
