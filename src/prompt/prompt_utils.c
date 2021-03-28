#include "../../includes/prompt.h"

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

void	insert(t_dlist **lst, char c, t_pos *pos)
{
	char	*s;
	t_dlist *new;

	s = ft_calloc(sizeof(char), 2);
	s[0] = c;
	new = ft_dlstnew(s);
	if (pos->cursor >= pos->max_rg)
		ft_dlstadd_back(lst, new);
	else if (pos->cursor <= pos->max_lf)
		ft_dlstadd_front(lst, new);
	else  // pos->max_lf < pos->cursor < pos->max_rg
		ft_dlstinsert(lst, new);
	return;
}

void init_pos(t_pos *pos, char *ps1)
{
	pos->max_lf = ft_strlen(ps1);
	pos->max_rg = ft_strlen(ps1);
	pos->cursor = ft_strlen(ps1);
	ft_putstr_fd(ps1, 1);
}
