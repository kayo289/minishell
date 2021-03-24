#include "../includes/prompt.h"

void del(t_pos *pos)
{
	if(pos->cursor > pos->max_lf)
	{
		write(1, "\b ", 2);
		ft_putstr_fd("\x1b[1D", 1);
		pos->cursor--;
	}
}

void lf(t_pos *pos)
{
	write(1, "\nminishell$ ", 12);
	pos->cursor = pos->max_lf;
	pos->max_rg = pos->cursor;
}

void esc(t_pos *pos)
{
	char	key;
	int		cnt;

	cnt = 0;
	read(0, &key, 1);
	while (key == ESC)
	{
		cnt++;
		read(0, &key, 1);
	}
	if(cnt%2==1)
		ft_putstr_fd("[",1);
	if (key == '[' && cnt % 2 == 0)
	{
		read(0, &key, 1);
		if(key == 'C')
		{
			// right
			if(pos->cursor < pos->max_rg)
			{
				ft_putstr_fd("\x1b[1C", 1);
				pos->cursor++;
			}
		}
		else if(key == 'D')
		{
			// left
			if(pos->max_lf < pos->cursor)
			{
				ft_putstr_fd("\x1b[1D", 1);
				pos->cursor--;
			}
		}
	}
}

static void prompt_loop(void)
{
	char *ps1 = "minishell$ ";
	char key;
	t_pos pos;

	pos.max_lf = ft_strlen(ps1);
	pos.max_rg = ft_strlen(ps1);
	pos.cursor = ft_strlen(ps1);
	write(1, ps1, ft_strlen(ps1));
	while(1)
	{
		read(0, &key, 1);
		//printf("key:%x\n", key);
		if (isprint(key))
			write(1, &key, 1);
		if (key == ESC)
			esc(&pos);
		else if (key == LF)
			lf(&pos);
		else if (key == DEL)
			del(&pos);
		else
		{
			pos.max_rg++;
			pos.cursor++;
		}
	}
	return;
}

void prompt(void)
{
	struct termio tty;
	struct termio tty_save;

	ioctl(0, TCGETA, &tty);
	tty_save = tty;
	tty.c_lflag ^= (ICANON | ECHO);
	tty.c_lflag |= ECHONL; 
	ioctl(0, TCSETA, &tty);
	prompt_loop();	
	ioctl(0, TCSETA, &tty_save);
	return;
}

// To debug
int main(void)
{
	prompt();
}
