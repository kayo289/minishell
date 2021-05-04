#include "../../includes/minishell.h"

static int		outc(int c)
{
	return write(1, &c, 1);
}

void			term_mode(char *p)
{
	char	buf[BUFFER_SIZE];
	char	*term;
	char	*cptr;
	int		n;

	if ((term = getenv("TERM")) == NULL)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	if (tgetent(buf, term) != 1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	cptr = buf;
	if (tgetstr(p, &cptr) != NULL)
		tputs(buf, 1, outc);
	else if ((n = tgetnum(p)) != -1)
		(void)printf("%d\n", n);
}

static int		prompt_input(t_dlist **cursor, char *ps, t_shell *shell)
{
	char	key;
	t_pos	pos;

	init_pos(&pos, ps);
	while(1)
	{
		read(0, &key, 1);
		if (key == CTRL_SPACE)
			select_mode(&pos, cursor);
		else if(key == CTRLV)
			paste(&pos, cursor, shell);
		else if(key == CTRLX)
			cut(&pos, cursor, shell);
		else if(key == CTRLY)
			copy(&pos, cursor, shell);

		else if (key == ESC)
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

static int		prompt_loop(char *ps, t_dlist **line, t_shell *shell)
{
	int	ret;

	ret = -1;
	while (ret != LF)
	{
		*line = ft_dlstnew(NULL);
		ft_putstr_fd(ps, 1);
		term_mode("im");
		ret = prompt_input(line, ps, shell);
		term_mode("ei");
		if (ret == CTRLC || ret == CTRLD)
		{
			*line = ft_dlsttop(*line);
			ft_dlstclear(line, free);
			if (ret == CTRLC)
				shell->exit_status = 1;
			else if (ret == CTRLD)
				return (CTRLD);
		}
	}
	return (LF);
}

void			prompt(char *ps, t_dlist **line, t_shell *shell)
{
	struct termios	tty;
	struct termios	tty_save;
	int				ret;
	t_dlist			*tmp;

	tcgetattr(STDIN_FILENO, &tty);
	tty_save = tty;
	tty.c_lflag ^= ((ICANON | ISIG | ECHO) & ~ECHONL);
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	ret = prompt_loop(ps, line, shell);
	tcsetattr(STDIN_FILENO, TCSANOW, &tty_save);
	if (ret == CTRLD)
	{
		ft_putendl_fd("exit", 1);
		ft_dlstclear(line, free);
		minishell_end(shell);
	}
	else if (ret == LF)
	{
		tmp = ft_dlsttop(*line);
		*line = tmp->next;
		ft_dlstdelone(tmp, free);
		save_history(*line, shell);
	}
}
