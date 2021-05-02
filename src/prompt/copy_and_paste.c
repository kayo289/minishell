#include "../../includes/minishell.h"

void select_mode(t_pos *pos, t_dlist **cursor)
{
	pos->start = (*cursor)->next;
}

void paste(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(shell->clipboard_path, O_RDONLY | O_CREAT, S_IREAD);
	if (fd < 0)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (line[i] != '\0')
			insert(cursor, line[i++], pos);
		free(line);
	}
	free(line);
	close(fd);
}

void copy(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	int		fd;
	t_dlist	*tmp;

	pos->end = *cursor;
	fd = open(shell->clipboard_path, O_WRONLY | O_CREAT, S_IWRITE);
	if (fd < 0 || pos->start == NULL || pos->end == NULL)
		return;
	if (pos->start > pos->end)
	{
		tmp = pos->start;
		pos->start = pos->end;
		pos->end = tmp;
	}
	while (pos->start < pos->end)
	{
		ft_putstr_fd((char *)pos->start->content, fd);
		pos->start = pos->start->next;
	}
	ft_putendl_fd((char *)pos->start->content, fd);
	close(fd);
}

void cut(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	int		fd;
	t_dlist	*tmp;

	pos->end = *cursor;
	fd = open(shell->clipboard_path, O_WRONLY | O_CREAT, S_IWRITE);
	if (fd < 0 || pos->start == NULL || pos->end == NULL)
		return;
	if (pos->start > pos->end)
	{
		tmp = pos->start;
		pos->start = pos->end;
		pos->end = tmp;
	}
	while (pos->start < pos->end)
	{
		ft_putstr_fd((char *)pos->start->content, fd);
		pos->start = pos->start->next;
	}
	ft_putendl_fd((char *)pos->start->content, fd);
	close(fd);
}

