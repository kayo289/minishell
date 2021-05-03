#include "../../includes/minishell.h"

void select_mode(t_pos *pos, t_dlist **cursor)
{
	pos->select.mode = true;
	pos->select.start = pos->cursor;
	pos->select.startp = *cursor;
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
	close(fd);
}

static void swap(t_pos *pos)
{
	int		tmp;
	t_dlist	*ptmp;

	tmp = pos->select.start;
	pos->select.start = pos->select.end;
	pos->select.end = tmp;

	ptmp = pos->select.startp;
	pos->select.startp = pos->select.endp;
	pos->select.endp = ptmp;
}

void copy(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	int		fd;

	if (!pos->select.mode)
		return;
	pos->select.mode = false;
	pos->select.end = pos->cursor;	
	pos->select.endp = *cursor;	
	fd = open(shell->clipboard_path, O_WRONLY | O_CREAT, S_IWRITE);
	if (fd < 0)
		return;
	if (pos->select.start > pos->select.end)
		swap(pos);
	while (pos->select.start < pos->select.end)
	{
		ft_putstr_fd((char *)pos->select.startp->content, fd);
		pos->select.startp = pos->select.startp->next;
		pos->select.start++;
	}
	ft_putendl_fd((char *)pos->select.startp->content, fd);
	close(fd);
}

void cut(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	copy(pos, cursor, shell);
}

