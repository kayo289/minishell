#include "../../includes/minishell.h"

#define MESSAGE1 "minishell: unexpected EOF while looking for matching "
#define MESSAGE2 "minishell: syntax error: unexpected end of file"

void err_syntax(t_ip **ip)
{
	ft_putstr_fd("syntax error near unexpected token ", 2); 
	ft_putendl_fd((*ip)->id_string, 2);
	(*ip)->sy = INPUT_END;
}

void err_notfound(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(": command not found", 2);
}
