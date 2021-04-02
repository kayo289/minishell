#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <termios.h>
#include <termcap.h>
#include <ctype.h>
#include <fcntl.h>
#include "libcmds.h"

#define CTRLC	3
#define CTRLD	4
#define LF		10
#define ESC		27
#define DEL		127
#define SIZE	29999

enum u_token;
struct s_ip;
struct s_pos;
struct s_shell;
struct s_param;
typedef struct s_shell *	t_shell;
typedef struct s_param		t_param;
typedef enum u_token		t_token;
typedef struct s_ip			t_ip;
typedef struct s_pos		t_pos;
typedef char ***			t_args;

enum u_token
{
	PIPE,		// |
	REDIRECT,	// >>, >, <
	LEFT_BRACE,	// {
	RIGHT_BRACE,// }
	SEMICOLON,	// ;
	IDENTIFY,	// String
	INPUT_END,	// End Of Input

	TOKEN_NUM	// don't care
};

struct	s_ip
{
	t_token		sy;
	char		ch;
	char		*id_string;
	/* To degug 
	char *command_name[TOKEN_NUM] = {
		"PIPE",			// |
		"REDIRECT",		// >, >>, <
		"LEFT_BRACE",	// {
		"RIGHT_BRACE",	// }
		"SEMICOLON",	// ;
		"IDENTIFY",		// String
		"INPUT_END"		// End Of Input
	};
	*/
};

struct  s_pos
{
	int cursor;
	int max_rg;
	int max_lf;
};

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

// prompt
void	prompt(char *ps, t_dlist **line);
void	term_mode(char *p);

// prompt_utils
void	insert(t_dlist **lst, char c, t_pos *pos);
void 	del(t_pos *pos, t_dlist **cursor);
void 	esc(t_pos *pos, t_dlist **cursor);
void	init_pos(t_pos *pos, char *ps);
void	ctrl_d(t_pos *pos, t_dlist **cursor);

// lexer
void lexer(t_dlist **line, t_queue *tokens);
void get_token(t_dlist **line, t_ip *ip, t_queue *tokens);
void save_token(t_ip *ip, t_queue *tokens);
char next_ch(t_dlist **line, t_ip *ip);
void literal(t_dlist **line, t_ip *ip, t_queue *tokens);
char *expand_parameter(t_dlist **line, t_ip *ip, t_queue *tokens);
void quoting(t_dlist **line, t_ip *ip, t_queue *tokens);
void metacharacter(t_dlist **line, t_ip *ip, t_queue *tokens);

// parser
void 	parser(t_queue *tokens, t_shell *shell);
void 	next_token(t_ip **ip, t_queue *tokens);
void	assign_variable(t_ip **ip, t_queue *tokens, t_shell *shell);

// interpreter
void exec_a(t_args args, t_queue *fds, int *ppfd[], t_shell *shell);
void exec_b(t_args args, t_queue *fds, int *ppfd[], t_shell *shell);
void redirect(t_queue *fds);
char *fetch_path(t_args args, t_shell *shell);

// error
void err_syntax(t_ip **ip);
void err_notfound(char *cmd);
void err_badfd(int n);

// shell_var
t_shell new_shell_var(void);
void set_shell_var(t_shell this, char *param);
char *get_shell_var(t_shell this, char *name);
int hash(char *name);

#endif
