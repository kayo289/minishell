#include "../../includes/minishell.h"

static int outc(int c)
{
	return write(1, &c, 1);
}

void term_mode(char *p)
{
	char buf[1024];
	char *term;
	char *cptr;

	if ((term = getenv("TERM")) == NULL)
		ft_putstr_fd("getenv\n", 2);
	if (tgetent(buf, term) != 1)
		ft_putstr_fd("tgetent\n", 2);
	cptr = buf;
	if (tgetstr(p, &cptr))
		tputs(buf, 1, outc);
}

static int prompt_input(t_dlist **cursor, char *ps)
{
	char key;
	t_pos pos;

	init_pos(&pos, ps);
	while(1)
	{
		read(0, &key, 1);
		if (key == ESC)
			esc(&pos, cursor);
		else if (key == DEL)
			del(&pos, cursor);
		else if (key == LF || key == CTRLC)
		{
			ft_putchar_fd('\n', 1);
			return (key);
		}
		else if (key == CTRLD)
		{
			if ((*cursor)->next == NULL && (*cursor)->prev == NULL)
				return (key);
			ctrld(&pos, cursor);
		}
		else if (ft_isprint(key))
			insert(cursor, key, &pos);
	}
}

void prompt(char *ps, t_dlist **line)
{
	struct termio	tty;
	struct termio	tty_save;
	t_dlist			*head;
	int				ret;

	ioctl(0, TCGETA, &tty);
	tty_save = tty;
	tty.c_lflag ^= ((ICANON | ISIG | ECHO) & ~ECHONL);
	ret = 0;
	while (ret != LF)
	{
		head = ft_dlstnew(NULL);
		*line = head;
		ft_putstr_fd(ps, 1);
		ioctl(0, TCSETA, &tty);
		term_mode("im");
		ret = prompt_input(&head, ps);
		term_mode("ei");
		ioctl(0, TCSETA, &tty_save);
		if (ret == CTRLC || ret == CTRLD)
		{
			ft_dlstclear(line, free);
			if (ret == CTRLC)
				continue;
			ft_putendl_fd("exit", 1);
			exit(0);
		}
	}
	ft_dlstadd_back(line, ft_dlstnew("\0"));
	*line = (*line)->next;
}
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
