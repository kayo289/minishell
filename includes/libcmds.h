#ifndef LIBCMDS_H
#define LIBCMDS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "libft.h"
#include "shell_var.h"


void cd(char **argv);
void pwd(char **argv);
void echo(char **argv);
void unset(char **argv, t_shell *shell);

#endif
