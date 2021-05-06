#include "../../includes/minishell.h"

void select_mode(t_pos *pos, t_dlist **cursor)
{
	pos->is_select = true;
	pos->select = pos->cursor;
	pos->selectp = *cursor;
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
	int		start;
	int		end;

	if (!pos->is_select)
		return;
	pos->is_select = false;
	start = pos->select;	
	end = pos->cursor;	
	if ((fd = open(shell->clipboard_path, O_WRONLY | O_TRUNC)) < 0)
		return;
	if (start > end)
	{
		swap(&start, &end);
		pos->selectp = *cursor;
	}
	while (start++ < end)
	{
		ft_putstr_fd((char *)pos->selectp->content, fd);
		pos->selectp = pos->selectp->next;
	}
	ft_putendl_fd((char *)pos->selectp->content, fd);
}

void cut(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	int	start;
	int	end;

	if (!pos->is_select)
		return;
	copy(pos, cursor, shell);
	if (pos->select > pos->cursor)
	{
		term_mode("ch", -1, pos->select);
		swap(&pos->select, &pos->cursor);
		*cursor = pos->selectp;
	}
	start = pos->select;
	end = pos->cursor;
	while (start++ <= end)
		delete(pos, cursor);
}
