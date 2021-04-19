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

void save_line(t_dlist *line, t_shell *shell)
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
		while ((*shell)->hist_lst->content != NULL)
			(*shell)->hist_lst = (*shell)->hist_lst->prev;
		ft_dlstinsert(&(*shell)->hist_lst, ft_dlstnew(buf));
		ft_putstr_fd(buf, fd);
		ft_putstr_fd("\n", fd);
	}
	close(fd);
}

void prompt(char *ps, t_dlist **line, t_shell *shell)
{
	struct termio	tty;
	struct termio	tty_save;
	int				ret;

	ioctl(0, TCGETA, &tty);
	tty_save = tty;
	tty.c_lflag ^= ((ICANON | ISIG | ECHO) & ~ECHONL);
	ret = 0;
	while (ret != LF)
	{
		*line = ft_dlstnew(NULL);
		ft_putstr_fd(ps, 1);

		ioctl(0, TCSETA, &tty);
		term_mode("im");
		ret = prompt_input(line, ps, shell);
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
	while ((*line)->prev != NULL)
		*line = (*line)->prev;
	*line = (*line)->next;
	save_line(*line, shell);
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
