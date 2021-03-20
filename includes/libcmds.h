#ifndef LIBCMDS_H 
#define LIBCMDS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void cd(int argc, char **argv);
void pwd(int argc, char **argv);
void echo(int argc, char **argv);


#endif
