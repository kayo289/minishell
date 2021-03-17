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
#include "get_next_line.h"

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
	int			index;
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

char *get_shell_var(char *name, char ***shell_var);
int set_shell_var(char *name, char *value, char ***shell_var);

// lexer
void parse_line(char *line, char ***shell);
void expand_parameter(char **line, t_ip *ip, char ***shell_var);
char next_ch(char *line, t_ip *ip);
void quoting(char **line, t_ip *ip, char ***shell_var);
void metacharacter(char **line, t_ip *ip);

// parser
void list(t_ip **ip, char ****args, t_list **queue, char ***shell_var);
void next_token(t_ip **ip, t_list **queue);
char **fetch_path(char ****args, char ***shell_var);
void go_exec_pipeline(char ****args, char ***shell_var);

void error(char *message, char *token);
void error2(char *message, char token);

#endif
