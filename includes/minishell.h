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

void exe_cmd(int i, char ***args, char **path);
void parse_line(char *line);
void get_token(char **line, t_ip *ip);
void input(char **line, t_ip *ip, char ****args);
void command(char **line, t_ip *ip, char ****args);
bool equal(char *s, char *t);
void error(char *message, char *token);
void set_signal(int p_signame);
void sig_handler(int p_signame);
char  **ft_realloc2(char **old, char *add);
char  ***ft_realloc3(char ***old, char **add);
char  **ft_calloc2(size_t nmemb, size_t size);
char  ***ft_calloc3(size_t nmemb, size_t size);


#endif
