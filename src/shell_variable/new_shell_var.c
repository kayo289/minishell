#include "../../includes/minishell.h"

static void init(t_shell *this)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		this->var[i] = NULL;
		i++;
	}
	this->histfile_path = NULL;
	this->hist_lst = NULL;
	this->clipboard_path = NULL;
	this->pwd = NULL;
	this->exit_status = 0;
}

static void open_clipboard(t_shell *shell)
{
	char 	*path;
	int		fd;

	fd = open(".minishell_clipboard", O_RDWR | O_CREAT, S_IWRITE | S_IREAD);
	if (fd < 0)
		return;
	path = getcwd(NULL, 0);
	shell->clipboard_path = ft_strjoin(path, "/.minishell_clipboard");
	free(path);
	close(fd);
}

static void read_history_file(t_shell *shell)
{
	char	*line;
	char 	*path;
	int		fd;

	if ((fd = open(".minishell_history", O_RDONLY | O_CREAT, S_IREAD | S_IWRITE)) < 0)
		return;
	path = getcwd(NULL, 0);
	shell->histfile_path = ft_strjoin(path, "/.minishell_history");
	while (get_next_line(fd, &line) > 0)
	{
		ft_dlstadd_front(&shell->hist_lst, ft_dlstnew(line));
		free(line);
	}
	ft_dlstadd_front(&shell->hist_lst, ft_dlstnew(NULL));
	free(line);
	free(path);
	close(fd);
}

void new_shell_var(t_shell *this)
{
	extern char	**environ;
	int			i;

	init(this);
	open_clipboard(this);
	read_history_file(this);
	i = 0;
	while (environ[i] != NULL)
	{
		set_shell_var(this, environ[i]);
		i++;
	}
}
