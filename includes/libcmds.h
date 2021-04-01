#ifndef LIBCMDS_H 
#define LIBCMDS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "libft.h"

void cd(char **argv);
void pwd(char **argv);
void echo(char **argv);


#endif
