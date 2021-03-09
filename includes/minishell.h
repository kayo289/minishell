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

// minishell.c
void exec_cmd(int i, char ***args, char **path);

// lexer
void parse_line(char *line);
void get_token(char **line, t_ip *ip);
char next_ch(char *line, t_ip *ip);
void quoting(char **line, t_ip *ip);
void parameter(char **line, t_ip *ip);
void metacharacter(char **line, t_ip *ip);
void error(char *message, char *token);

// parser
void input(char **line, t_ip *ip, char ****args);
char **fetch_path(char ****args);
void error2(char *message, char token);

// share
char *ft_getenv(char *key);
bool equal(char *s, char *t);

#endif
