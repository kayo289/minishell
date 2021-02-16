#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "get_next_line.h"

void minish_cd();
void minish_pwd();
void minish_echo();
void minish_env();
void minish_export();
void minish_unset();
void minish_exit();

#endif
