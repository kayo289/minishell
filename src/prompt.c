#include "../includes/prompt.h"

static int outc(int c)
{
	return write(1, &c, 1);
}

static void term_mode(char *p)
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

void del(t_pos *pos)
{
	if (pos->cursor >= pos->max_lf)
	{
		write(1, "\b", 1);
		term_mode("dc");
		pos->cursor--;
		pos->max_lf--;
	}
}

void esc(t_pos *pos)
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
				pos->cursor++;
				term_mode("nd"); // cursor_right
			}
		}
		else if(key == 'D')
		{
			if(pos->max_lf < pos->cursor)
			{
				pos->cursor--;
				term_mode("le"); // cursor_left
			}
		}
	}
}

void init_pos(t_pos *pos, char *ps1)
{
	pos->max_lf = ft_strlen(ps1);
	pos->max_rg = ft_strlen(ps1);
	pos->cursor = ft_strlen(ps1);
	ft_putstr_fd(ps1, 1);
}

static void prompt_loop(char *ps1)
{
	char key;
	t_pos pos;

	term_mode("im"); // enter_insert_mode
	init_pos(&pos, ps1);
	while(1)
	{
		read(0, &key, 1);
		if (key == ESC)
			esc(&pos);
		else if (key == DEL)
			del(&pos);
		else if (key == LF)
		{
			ft_putchar_fd('\n', 1);
			init_pos(&pos, ps1);
		}
		else if (key == ETX) // Ctrl+C
		{
			//parser(line);
			ft_putchar_fd('\n', 1);
			init_pos(&pos, ps1);
		}
		else if (key == EOT) // Ctrl+D
		{
			ft_putendl_fd("exit", 1);
			return;
		}
		else if (ft_isprint(key))
		{
			pos.max_rg++;
			pos.cursor++;
			ft_putchar_fd(key, 1);
		}
	}
}

void prompt(void)
{
	struct termio tty;
	struct termio tty_save;

	ioctl(0, TCGETA, &tty);
	tty_save = tty;
	tty.c_lflag ^= (ICANON | ISIG | ECHO);
	tty.c_lflag |= ECHONL; 
	ioctl(0, TCSETA, &tty);

	prompt_loop("minishell$ ");
	term_mode("ei"); // exit_insert_mode

	ioctl(0, TCSETA, &tty_save);
}

// To debug
int main(void)
{
	prompt();
}
