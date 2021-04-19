#ifndef LIBCMDS_H
#define LIBCMDS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "libft.h"

#define SIZE	29999

struct s_shell;
struct s_param;
typedef struct s_param		t_param;
typedef struct s_shell *	t_shell;

struct s_shell
{
	t_list	*var[SIZE];
	int		exit_status;
};

struct s_param
{
	char *key;
	char *value;
};

void cd(char **argv);
void pwd(char **argv);
void echo(char **argv);
void unset(char **argv, t_shell *shell);

#endif
