#include "../../includes/minishell.h"

void init(t_shell *this)
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
	this->exit_status = 0;
}

void read_history_file(t_shell *shell)
{
	char	*line;
	char 	*path;
	int		fd;

	if ((fd = open(".minishell_history", O_RDONLY)) < 0)
		return;
	path = getcwd(NULL, 0);
	shell->histfile_path = ft_strjoin(path, "/.minishell_history");
	while (get_next_line(fd, &line) > 0)
	{
		ft_dlstadd_front(&shell->hist_lst, ft_dlstnew(line));
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
	read_history_file(this);
	i = 0;
	while (environ[i] != NULL)
	{
		set_shell_var(this, environ[i]);
		i++;
	}
}
