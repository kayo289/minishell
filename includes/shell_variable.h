#ifndef SHELL_VARIABLE_H
#define	SHELL_VARIABLE_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft.h"

#define HASH_SIZE 29999

struct s_shell_var;
struct s_param;
typedef struct s_shell_var * t_shell_var;
typedef struct s_param t_param;

struct s_shell_var
{
	t_list *hash_table[HASH_SIZE];
};

struct s_param
{
	char *key;
	char *value;
};

t_shell_var new_shell_var(void);
void set_shell_var(t_shell_var this, char *param);
char *get_shell_var(t_shell_var this, char *name);
int hash(char *name);

#endif
