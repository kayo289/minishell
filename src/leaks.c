#include "../includes/leaks.h"

#if LEAKS

void	end(void)
{
	system("leaks minishell_leaks");
}

#endif

