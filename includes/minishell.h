#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
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

typedef struct	s_ip
{
	t_token		sy;
	char		ch;
	char		*id_string;
}				t_ip;

void get_token(char **line, t_ip *ip);
void input(char **line, t_ip *ip);
void command(char **line, t_ip *ip);
bool equal(char *s, char *t);
void error(char *message, char *token);

#endif
