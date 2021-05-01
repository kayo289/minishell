#include "../../includes/minishell.h"

void		init_pos(t_pos *pos, char *ps)
{
	pos->max_lf = ft_strlen(ps);
	pos->cursor = ft_strlen(ps);
	pos->max_rg = ft_strlen(ps);
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
