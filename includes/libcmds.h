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


void minishell_cd(char **argv, t_shell *shell);
void minishell_pwd(char **argv);
void minishell_echo(char **argv);
void minishell_unset(char **argv, t_shell *shell);
void minishell_exit(char **argv, t_shell *shell);

#endif
