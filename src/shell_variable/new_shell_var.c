#include "../../includes/minishell.h"

void init(t_shell *this)
{
	//t_dlist *head;
	int	i;

	*this = malloc(sizeof(t_shell));
	i = 0;
	while (i < SIZE)
	{
		(*this)->var[i] = malloc(sizeof(t_list)); 
		(*this)->var[i] = NULL;
		i++;
	}
	(*this)->hist_lst = NULL;
	(*this)->exit_status = 0;
}

void read_history_file(t_shell *shell)
{
	char		*line;
	int			fd;

	if ((fd = open(".minishell_history", O_RDONLY)) < 0)
		return;
	while (get_next_line(fd, &line) > 0)
	{
		ft_dlstadd_front(&(*shell)->hist_lst, ft_dlstnew(line));
		//free(line);
	}
	ft_dlstadd_front(&(*shell)->hist_lst, ft_dlstnew(NULL));
	free(line);
	close(fd);
}

t_shell new_shell_var(void)
{
	extern char	**environ;
	t_shell		this;
	int			i;

	init(&this);
	read_history_file(&this);

	i = -1;
	while (environ[++i] != NULL)
		set_shell_var(this, environ[i]);

	return (this);
}
