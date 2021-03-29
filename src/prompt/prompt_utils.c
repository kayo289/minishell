#include "../../includes/minishell.h"

void init_pos(t_pos *pos, char *ps)
{
	pos->max_lf = ft_strlen(ps);
	pos->cursor = ft_strlen(ps);
	pos->max_rg = ft_strlen(ps);
}

void del(t_pos *pos, t_dlist **cursor)
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

void esc(t_pos *pos, t_dlist **cursor)
{
	char	key;

	read(0, &key, 1);
	if (key == '[')
	{
		read(0, &key, 1);
		if(key == 'A')
			return;// histroy
		if(key == 'B')
			return;// histroy
		if(key == 'C')
		{
			if(pos->cursor < pos->max_rg)
			{
				*cursor = (*cursor)->next;
				pos->cursor++;
				term_mode("nd");
			}
		}
		if(key == 'D')
		{
			if(pos->max_lf < pos->cursor)
			{
				*cursor = (*cursor)->prev;
				pos->cursor--;
				term_mode("le");
			}
		}
	}
}

void	insert(t_dlist **lst, char c, t_pos *pos)
{
	char	*s;
	t_dlist *new;

	s = ft_calloc(sizeof(char), 2);
	s[0] = c;
	new = ft_dlstnew(s);
	if (pos->cursor >= pos->max_rg)
		ft_dlstadd_back(lst, new);
	else
		ft_dlstinsert(lst, new);
	*lst = (*lst)->next;
	ft_putchar_fd(c, 1);
	pos->max_rg++;
	pos->cursor++;
}

void ctrld(t_pos *pos, t_dlist **cursor)
{
	if (pos->cursor != pos->max_rg)
	{
		*cursor = (*cursor)->next;
		ft_dlstdelone(*cursor, free);
		term_mode("dc");
		pos->max_rg--;
	}
}
