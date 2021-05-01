#include "../../includes/minishell.h"

static void		move_to_rg(t_pos *pos, t_dlist **cursor)
{
	if(pos->cursor < pos->max_rg)
	{
		*cursor = (*cursor)->next;
		pos->cursor++;
		term_mode("nd");
	}
}

static void		move_to_lf(t_pos *pos, t_dlist **cursor)
{
	if(pos->max_lf < pos->cursor)
	{
		*cursor = (*cursor)->prev;
		pos->cursor--;
		term_mode("le");
	}
}

static void		move_to_next_word(t_pos *pos, t_dlist **cursor)
{
	if(pos->cursor >= pos->max_rg)
		return;
	move_to_rg(pos, cursor);
	while (*(char *)(*cursor)->content == ' ')
	{
		move_to_rg(pos, cursor);
		if (pos->cursor >= pos->max_rg)
			return;
	}
	while (*(char *)(*cursor)->content != ' ')
	{
		move_to_rg(pos, cursor);
		if (pos->cursor >= pos->max_rg)
			return;
	}
	move_to_lf(pos, cursor);
}

static void		move_to_prev_word(t_pos *pos, t_dlist **cursor)
{
	if(pos->max_lf >= pos->cursor)
		return;
	while (*(char *)(*cursor)->content == ' ')
	{
		move_to_lf(pos, cursor);
		if(pos->max_lf >= pos->cursor)
			return;
	}
	while (*(char *)(*cursor)->content != ' ')
	{
		move_to_lf(pos, cursor);
		if(pos->max_lf >= pos->cursor)
			return;
	}
}

void		move(t_pos *pos, t_dlist **cursor, t_shell *shell)
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
		else if(key == '1')
		{
			read(0, &key, 1);
			if(key == ';')
			{
				read(0, &key, 1);
				if(key == '5')
				{
					read(0, &key, 1);
					if(key == 'C')
						move_to_next_word(pos, cursor);
					else if(key == 'D')
						move_to_prev_word(pos, cursor);
				}
			}
		}
	}
}

