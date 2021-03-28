#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <stdbool.h>
#include "libcmds.h"
#include "prompt.h"
#include "shell_variable.h"

typedef enum u_token
{
	PIPE,		// |
	GT,			// >
	LT,			// < 
	DGT,		// >>
	SEMICOLON,	// ;
	IDENTIFY,	// String
	INPUT_END,	// End Of Input

	TOKEN_NUM	// don't care
} t_token;

typedef struct	s_ip
{
	t_token		sy;
	char		ch;
	char		*id_string;
	/* To degug 
	char *command_name[TOKEN_NUM] = {
		"PIPE",		// |
		"GT",		// >
		"LT",		// < 
		"DGT",		// >>
		"SEMICOLON",// ;
		"IDENTIFY", // String
		"INPUT_END"	// End Of Input
	};
	*/
}				t_ip;

typedef t_list * t_queue;
typedef char *** t_args;

// lexer
void lexer(t_dlist **line, t_queue *tokens, t_shell_var *sv);
char next_ch(t_dlist **line, t_ip *ip);
char *expand_parameter(t_dlist **line);
void quoting(t_dlist **line, t_ip *ip);
void metacharacter(t_dlist **line, t_ip *ip);

// parser
void parser(t_queue *tokens, t_shell_var *sv);

// exec_unit
void exec(t_args *args, t_shell_var *sv, t_queue *vars);
char **fetch_path(t_args *args, t_shell_var *sv);

void error(char *message, char *token);
void error2(char *message, char token);

#endif
