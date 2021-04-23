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
	{
		ft_putstr_fd(strerror(errno), 2);
		return;
	}
	if (tgetent(buf, term) != 1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return;
	}
	cptr = buf;
	if (tgetstr(p, &cptr))
		tputs(buf, 1, outc);
}

static int prompt_input(t_dlist **cursor, char *ps, t_shell *shell)
{
	char key;
	t_pos pos;

	init_pos(&pos, ps);
	while(1)
	{
		read(0, &key, 1);
		if (key == ESC)
			esc(&pos, cursor, shell);
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
			ctrl_d(&pos, cursor);
		}
		else if (ft_isprint(key))
			insert(cursor, key, &pos);
	}
}

static int prompt_loop(char *ps, t_dlist **line, t_shell *shell)
{
	int	ret;

	ret = 0;
	while (ret != LF)
	{
		*line = ft_dlstnew(NULL);
		ft_putstr_fd(ps, 1);
		term_mode("im");
		ret = prompt_input(line, ps, shell);
		term_mode("ei");
		if (ret == CTRLC || ret == CTRLD)
		{
			ft_dlstclear(line, free);
			if (ret == CTRLD)
				return (CTRLD);
		}
	}
	return (LF);
}

void prompt(char *ps, t_dlist **line, t_shell *shell)
{
	struct termio	tty;
	struct termio	tty_save;
	int				ret;

	ioctl(0, TCGETA, &tty);
	tty_save = tty;
	tty.c_lflag ^= ((ICANON | ISIG | ECHO) & ~ECHONL);
	ioctl(0, TCSETA, &tty);
	ret = prompt_loop(ps, line, shell);
	ioctl(0, TCSETA, &tty_save);
	if (ret == CTRLD)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (ret == LF)
	{
		ft_dlstadd_back(line, ft_dlstnew("\0"));
		while ((*line)->prev != NULL)
			*line = (*line)->prev;
		*line = (*line)->next;
		save_history(*line, shell);
	}
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
