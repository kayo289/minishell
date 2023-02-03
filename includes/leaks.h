#ifndef LEAKS_H
# define LEAKS_H

# include <stdlib.h>

void	end(void) __attribute__((destructor));

#endif
