#include "../../includes/minishell.h"

static void gt(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT, S_IWRITE | S_IREAD);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return;
	}
	dup2(fd, 1);
}

static void dgt(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE | S_IREAD);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return;
	}
	dup2(fd, 1);
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
	char *rdct;
	char *file;

	while (*fds != NULL)
	{
		rdct = pop(fds);
		file = pop(fds);
		if (ft_strcmp(rdct, ">") == 0)
			gt(file);
		else if (ft_strcmp(rdct, ">>") == 0)
			dgt(file);
		else if (ft_strcmp(rdct, "<") == 0)
			lt(file);
	}
}
