#include "../../includes/minishell.h"

static int gt(char *file, int n, t_shell *shell)
{
	int fd;

	if (n == INIT)
		n = STDOUT_FILENO;
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IWRITE | S_IREAD);
	if (fd == -1)
	{
		perror("Error\n");
		shell->exit_status = 1;
		return FAIL;
	}
	dup2(fd, n);
	return SUCCESS;
}

static int dgt(char *file, int n, t_shell *shell)
{
	int fd;

	if (n == INIT)
		n = STDOUT_FILENO;
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE | S_IREAD);
	if (fd == -1)
	{
		perror("Error\n");
		shell->exit_status = 1;
		return FAIL;
	}
	dup2(fd, n);
	return SUCCESS;
}

static int lt(char *file, int n, t_shell *shell)
{
	int fd;

	if (n == INIT)
		n = STDIN_FILENO;
	if ((fd = open(file, O_RDWR)) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		shell->exit_status = 1;
		return FAIL;
	}
	dup2(fd, n);
	return SUCCESS;
}

static int get_file_descriptor(char **rdt)
{
	int n;

	if (!ft_isalnum(**rdt))
		return (INIT);
	n = 0;
	while (ft_isalnum(**rdt))
	{
		if (n > (INT_MAX - (**rdt - '0')) / 10)
			return (OUTOFRANGE);
		n = n * 10 + (**rdt - '0');
		(*rdt)++;
	}
	return (n);
}

int redirect(t_queue *fds, t_shell *shell)
{
	int		n;
	int		result;
	char	*rdt;
	char	*file_name;
	char	**expand_file_name;

	result = SUCCESS;
	while (!q_empty(fds))
	{
		rdt = deq(fds);
		file_name = deq(fds);
		n = get_file_descriptor(&rdt);
		if (n > 256 || n == OUTOFRANGE)
		{
			ft_putstr_fd("minishell: ", 2);
			if (n > 256)
				ft_putnbr_fd(n, 2);
			else 
				ft_putstr_fd("file descriptor out of range", 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd("Bad file descriptor", 2);
			shell->exit_status = 1;
			return FAIL;
		}
		expand_file_name = expand_word(file_name, shell, true);
		if (expand_file_name[0] == NULL || expand_file_name[1] != NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file_name, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd("ambiguous redirect", 2);
			shell->exit_status = 1;
			return FAIL;
		}
		if (ft_strcmp(rdt, ">>") == EQUAL)
			result = dgt(*expand_file_name, n, shell);
		else if (ft_strcmp(rdt, ">") == EQUAL)
			result = gt(*expand_file_name, n, shell);
		else if (ft_strcmp(rdt, "<<") == EQUAL)
			here_documents(file_name, shell);
		else if (ft_strcmp(rdt, "<") == EQUAL)
			result = lt(*expand_file_name, n, shell);
		dp_free(expand_file_name);
		if (result == FAIL)
			return FAIL;
	}
	return SUCCESS;
}
