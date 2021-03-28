#include "../../includes/prompt.h"

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
		if(key == 'C')
		{
			if(pos->cursor < pos->max_rg)
			{
				*cursor = (*cursor)->next;
				pos->cursor++;
				term_mode("nd"); // cursor_right
			}
		}
		else if(key == 'D')
		{
			if(pos->max_lf < pos->cursor)
			{
				*cursor = (*cursor)->prev;
				pos->cursor--;
				term_mode("le"); // cursor_left
			}
		}
	}
}

static void prompt_loop(char *ps, t_dlist **cursor)
{
	char key;
	t_pos pos;

	term_mode("im"); // enter_insert_mode
	init_pos(&pos, ps);
	while(1)
	{
		read(0, &key, 1);
		if (key == ESC)
			esc(&pos, cursor);
		else if (key == DEL)
			del(&pos, cursor);
		else if (key == LF)
		{
			ft_putchar_fd('\n', 1);
			return;
		}
		else if (key == ETX) // Ctrl+C
		{
			ft_putchar_fd('\n', 1);
			init_pos(&pos, ps);
		}
		else if (key == EOT) // Ctrl+D
		{
			ft_putendl_fd("exit", 1);
			term_mode("ei"); // exit_insert_mode
			exit(0);
		}
		else if (ft_isprint(key))
		{
			ft_putchar_fd(key, 1);
			insert(cursor, key, &pos);
			*cursor = (*cursor)->next;
			pos.max_rg++;
			pos.cursor++;
		}
	}
}

void prompt(char *ps, t_dlist **line)
{
	struct termio tty;
	struct termio tty_save;
	t_dlist *head;

	head = ft_dlstnew(NULL);
	*line = head;
	ioctl(0, TCGETA, &tty);
	tty_save = tty;
	tty.c_lflag ^= (ICANON | ISIG | ECHO);
	tty.c_lflag |= ECHONL; 
	ioctl(0, TCSETA, &tty);

	prompt_loop(ps, &head);
	term_mode("ei"); // exit_insert_mode

	ioctl(0, TCSETA, &tty_save);
	ft_dlstadd_back(line, ft_dlstnew("\0"));
	*line = (*line)->next;

	// To debug
	/*
	ft_putstr_fd("start output\n[", 1);
	while(*line != NULL)
	{
		write(1, (char *)((*line)->content), 1);
		*line = (*line)->next;
	}
	ft_putstr_fd("]\nend output\n", 1);
	*/
}
