#include "../../includes/minishell.h"

void		save_history(t_dlist *line, t_shell *shell)
{
	int		fd;
	char	*buf;
	char	*tmp;

	if((fd = open(shell->histfile_path, O_WRONLY | O_APPEND)) < 0)
		return;
	buf = ft_calloc(sizeof(char), 1);
	while (line != NULL)
	{
		tmp = buf;
		buf = ft_strjoin(buf, (char*)line->content);
		free(tmp);
		line = line->next;
	}
	if (*buf != '\0')
	{
		ft_putendl_fd(buf, fd);
		shell->hist_lst = ft_dlsttop(shell->hist_lst);
		ft_dlstinsert(&shell->hist_lst, ft_dlstnew(buf));
	}
	else
		free(buf);
	close(fd);
}

static void	clear_input(t_pos *pos, t_dlist **cursor)
{
	struct winsize	ws;
	int				i;
	int				n;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return;
	i = 0;
	n = pos->cursor / ws.ws_col;
	while (i < n)
	{
		term_mode("up", -1, -1);
		i++;
	}
	term_mode("ch", -1, pos->max_lf);
	term_mode("cd", -1, -1);

	init_pos(pos, "minishell$ ");
	*cursor = ft_dlsttop(*cursor);
	ft_dlstclear(cursor, free);
	*cursor = ft_dlstnew(NULL);
}

static void generate_prompt(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	char	*line;
	int		i;

	line = (char *)shell->hist_lst->content;
	if (line == NULL)
		return;
	i = 0;
	while (line[i] != '\0')
	{
		insert(cursor, line[i], pos);
		i++;
	}
}

void		history_prev(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	if (shell->hist_lst->next == NULL)
		return;
	clear_input(pos, cursor);
	shell->hist_lst = shell->hist_lst->next;
	generate_prompt(pos, cursor, shell);
}

void		history_next(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	if (shell->hist_lst->prev == NULL)
		return;
	clear_input(pos, cursor);
	shell->hist_lst = shell->hist_lst->prev;
	generate_prompt(pos, cursor, shell);
}

