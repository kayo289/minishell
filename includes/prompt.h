#ifndef PROMPT_H
#define PROMPT_H

#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termcap.h>
#include <ctype.h>
#include "libft.h"

#define ESC	0x1b
#define LF	0x0a
#define DEL 0x7f
#define ETX 3
#define EOT 4

typedef struct s_pos
{
	unsigned int cursor;
	unsigned int max_rg;
	unsigned int max_lf;
}				t_pos;

// prompt
void prompt(char *ps, t_dlist **line);

// prompt_utils
void 	term_mode(char *p);
void	init_pos(t_pos *pos, char *ps1);
void	insert(t_dlist **lst, char c, t_pos *pos);

#endif
