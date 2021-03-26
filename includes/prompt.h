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


void prompt(void);

#endif
