#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
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
#include "queue.h"
#include "libft.h"

#define CTRLC	3
#define CTRLD	4
#define LF		10
#define ESC		27
#define DEL		127
#define EXEC	1
#define UNEXEC	0
#define SUCESS	1
#define END		0
#define ERROR	-1
#define SIZE	29999

enum u_token;
enum u_grammer;
struct s_pos;
struct s_ip;
struct s_data;
struct s_shell;
struct s_param;
typedef enum u_token		t_token;
typedef enum u_grammer		t_grammer;
typedef struct s_pos		t_pos;
typedef struct s_ip			t_ip;
typedef struct s_data		t_data;
typedef struct s_param		t_param;
typedef struct s_shell *	t_shell;

enum u_token
{
	PIPE,		// |
	REDIRECT,	// >>, >, <
	LEFT_BRACE,	// {
	RIGHT_BRACE,// }
	SEMICOLON,	// ;
	IDENTIFY,	// String
	INPUT_END,	// End Of Input
	ERR,	// End Of Input

	TOKEN_NUM	// don't care
};

enum u_grammer
{
	SIMPLECMD,
	PIPELINE,
	
	GRAMMER_NUM	// don't care
};

struct s_shell
{
	t_list	*var[SIZE];
	t_dlist	*hist_lst;
	int		exit_status;
};

struct s_param
{
	char *key;
	char *value;
};

struct  s_pos
{
	int cursor;
	int max_rg;
	int max_lf;
};

struct	s_ip
{
	t_token		sy;
	char		ch;
	char		*id_string;
};

struct	s_data
{
	t_grammer	grammer;
	t_queue		vars;
	t_queue		fds;
	t_list		*args;
};


// prompt
void	prompt(char *ps, t_dlist **line, t_shell *shell);
void	term_mode(char *p);

// prompt_utils
void	insert(t_dlist **lst, char c, t_pos *pos);
void 	del(t_pos *pos, t_dlist **cursor);
void	esc(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	init_pos(t_pos *pos, char *ps);
void	ctrl_d(t_pos *pos, t_dlist **cursor);

// history
void	history_next(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	history_prev(t_pos *pos, t_dlist **cursor, t_shell *shell);
void	save_history(t_dlist *line, t_shell *shell);

// lexer
void	lexer(t_dlist **line, t_list **tokens, t_shell *shell);
void	get_token(t_dlist **line, t_ip *ip, t_list **tokens, t_shell *shell);
void	save_token(t_ip *ip, t_list **tokens);
char	next_ch(t_dlist **line, t_ip *ip);
void	literal(t_dlist **line, t_ip *ip, t_list **tokens, t_shell *shell);
char	*expand_parameter(t_dlist **line, t_ip *ip, t_shell *shell);
void	quoting(t_dlist **line, t_ip *ip, t_shell *shell);
void	metacharacter(t_dlist **line, t_ip *ip, t_list **tokens);

// parser
void	parser(t_list *tokens, t_shell *shell);

// interpreter
void	interpreter(t_list *datas, t_shell *shell);
void	assign_variable(t_list *datas, t_shell *shell);
void	redirect(t_list *datas, t_shell *shell);
void	set_signal(void);
void	cmd_execute(char **args, t_shell *shell);
int		bltin_execute(char **args, t_shell *shell);

// bltin
int minishell_cd(char **argv);
int minishell_pwd(char **argv);
int minishell_echo(char **argv);
int minishell_unset(char **argv, t_shell *shell);
int minishell_exit(char **argv, t_shell *shell);
int minishell_export(char **argv, t_shell *shell);

// error
void	err_syntax(t_ip **ip, t_shell *shell);
void	err_notfound(char *cmd, t_shell *shell);
void	err_badfd(int n, t_shell *shell);

// shell_var
t_shell	new_shell_var(void);
void	set_shell_var(t_shell this, char *param);
char	*get_shell_var(t_shell this, char *name);
int		get_next_line(int fd, char **line);
int		hash(char *name);


#endif
