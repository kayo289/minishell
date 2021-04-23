#include "../../includes/minishell.h"

void save_history(t_dlist *line, t_shell *shell)
{
	int fd;
	char *buf;

	if ((fd = open(".minishell_history", O_WRONLY | O_APPEND)) < 0)
		return;
	buf = ft_calloc(sizeof(char), 1);
	while (line != NULL)
	{
		buf = ft_strjoin(buf, (char*)line->content);
		line = line->next;
	}
	if (*buf != '\0')
	{
		ft_dlstinsert(&(*shell)->hist_lst, ft_dlstnew(buf));
		ft_putendl_fd(buf, fd);
	}
	close(fd);
}

static void clear_prompt(t_pos *pos)
{
	int i;
	
	i = 0;
	while (i < pos->cursor - pos->max_lf)
	{
		write(1, "\033[1D", 4);
		i++;
	}
	write(1, "\033[0K", 4);
	init_pos(pos, "minishell$ "); // * Causion "Use PS1"
}

static void generate_prompt(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	char *line;
	char *s;
	int i;

	line = (char *)(*shell)->hist_lst->content;
	*cursor = ft_dlstnew(NULL);
	if (line == NULL)
		return;
	i = -1;
	while (line[++i] != '\0')
	{
		s = ft_calloc(sizeof(char), 2);
		s[0] = line[i];
		ft_putstr_fd(s, 1);
		pos->cursor++;
		pos->max_rg++;
		ft_dlstadd_back(cursor, ft_dlstnew(s));
	}
	*cursor = ft_dlstlast(*cursor);
}

void history_prev(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	if ((*shell)->hist_lst->next == NULL)
		return;
	if (pos->cursor > pos->max_lf)
		clear_prompt(pos);
	(*shell)->hist_lst = (*shell)->hist_lst->next;
	generate_prompt(pos, cursor, shell);
}

void history_next(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	if ((*shell)->hist_lst->prev == NULL)
		return;
	if (pos->cursor > pos->max_lf)
		clear_prompt(pos);
	(*shell)->hist_lst = (*shell)->hist_lst->prev;
	generate_prompt(pos, cursor, shell);
}

