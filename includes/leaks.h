#ifndef LEAKS
#  define LEAKS 0
# endif

# if LEAKS
#include <stdlib.h>

void	end(void) __attribute__((destructor));

# endif


