#include "../../includes/minishell.h"

void select_mode(t_pos *pos, t_dlist **cursor)
{
	pos->select.mode = true;
	pos->select.start = pos->cursor;
	pos->select.p = *cursor;
}

void paste(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(shell->clipboard_path, O_RDONLY);
	if (fd < 0)
		return ;
	if (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (line[i] != '\0')
			insert(cursor, line[i++], pos);
	}
	free(line);
}

static void swap(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void copy(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	int		fd;
	int		i;

	if (!pos->select.mode)
		return;
	pos->select.mode = false;
	pos->select.end = pos->cursor;	
	if ((fd = open(shell->clipboard_path, O_WRONLY | O_TRUNC)) < 0)
		return;
	if (pos->select.start > pos->select.end)
	{
		swap(&pos->select.start, &pos->select.end);
		pos->select.p = *cursor;
	}
	i = pos->select.start;
	while (i++ < pos->select.end)
	{
		ft_putstr_fd((char *)pos->select.p->content, fd);
		pos->select.p = pos->select.p->next;
	}
	ft_putendl_fd((char *)pos->select.p->content, fd);
}

void cut(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	if (!pos->select.mode)
		return;
	copy(pos, cursor, shell);
	if (pos->select.start < pos->select.end)
	{
		while (pos->select.start++ < pos->select.end)
			del(pos, cursor);
	}
}
