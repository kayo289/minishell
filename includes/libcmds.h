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


int minishell_cd(char **argv);
int minishell_pwd(char **argv);
int minishell_echo(char **argv);
int minishell_unset(char **argv, t_shell *shell);
int minishell_exit(char **argv, t_shell *shell);

#endif
