#include "../../includes/minishell.h"

void		init_pos(t_pos *pos, char *ps)
{
	pos->cursor = ft_strlen(ps);
	pos->max_lf = ft_strlen(ps);
	pos->max_rg = ft_strlen(ps);

	pos->is_select = false;
	pos->select = ft_strlen(ps);
	pos->selectp = NULL;
}

void		backspace(t_pos *pos, t_dlist **cursor)
{
	t_dlist *tmp;

	if (pos->max_lf < pos->cursor)
	{
		tmp = *cursor;
		move_to_lf(pos, cursor);
		term_mode("dc", -1, -1);
		pos->max_rg--;
		ft_dlstdelone(tmp, free);
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

	ft_putchar_fd(c, 1);
	s = ft_calloc(sizeof(char), 2);
	s[0] = c;
	new = ft_dlstnew(s);
	if (pos->cursor < pos->max_rg)
		ft_dlstinsert(cursor, new);
	else
		ft_dlstadd_back(cursor, new);
	*cursor = (*cursor)->next;
	pos->max_rg++;
	pos->cursor++;
}

void		delete(t_pos *pos, t_dlist **cursor)
{
	if (pos->cursor < pos->max_rg)
	{
		ft_dlstdelone((*cursor)->next, free);
		term_mode("dc", -1, -1);
		pos->max_rg--;
	}
}
