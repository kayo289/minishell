#include "../../includes/minishell.h"

void		init_pos(t_pos *pos, char *ps)
{
	pos->cursor = ft_strlen(ps);
	pos->max_lf = ft_strlen(ps);
	pos->max_rg = ft_strlen(ps);
	pos->start = 0;
	pos->end = 0;
}

void		del(t_pos *pos, t_dlist **cursor)
{
	t_dlist *save;

	if (pos->cursor > pos->max_lf)
	{
		write(1, "\b", 1);
		term_mode("dc");
		save = (*cursor)->prev;
		ft_dlstdelone(*cursor, free);
		*cursor = save;
		pos->cursor--;
		pos->max_rg--;
	}
}

void		esc(t_pos *pos, t_dlist **cursor, t_shell *shell)
{
	char	key;

	read(0, &key, 1);
	if (key == '[')
	{
		read(0, &key, 1);
		if(key == 'A')
			history_prev(pos, cursor, shell);
		else if(key == 'B')
			history_next(pos, cursor, shell);
		else if(key == 'C')
			move_to_rg(pos, cursor);
		else if(key == 'D')
			move_to_lf(pos, cursor);
		else if(key == 'F')
			move_to_end(pos, cursor);
		else if(key == 'H')
			move_to_home(pos, cursor);
		else if(key == '1')
			move_to_word(pos, cursor);
	}
}

void		insert(t_dlist **cursor, char c, t_pos *pos)
{
	char	*s;
	t_dlist *new;

	s = ft_calloc(sizeof(char), 2);
	s[0] = c;
	new = ft_dlstnew(s);
	if (pos->cursor >= pos->max_rg)
		ft_dlstadd_back(cursor, new);
	else
		ft_dlstinsert(cursor, new);
	*cursor = (*cursor)->next;
	ft_putchar_fd(c, 1);
	pos->max_rg++;
	pos->cursor++;
}

void		ctrl_d(t_pos *pos, t_dlist **cursor)
{
	if (pos->cursor < pos->max_rg)
	{
		ft_dlstdelone((*cursor)->next, free);
		term_mode("dc");
		pos->max_rg--;
	}
}
