#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include "get_next_line.h"

void set_signal(int p_signame);
void sig_handler(int p_signame);

#endif
